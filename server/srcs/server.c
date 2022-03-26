/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:58:32 by sbelondr          #+#    #+#             */
/*   Updated: 2022/03/26 11:09:43 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "functions.h"

static t_srv **g_srv = NULL;

void ft_quit(int sig)
{
	printf("Kill all clients\n");
	t_srv *srv = *g_srv;
	int i = -1;
	int sd;

	if (srv->param->replay_fd)
		close(srv->param->replay_fd);
	while (srv && ++i < srv->param->allowed_clients_amount)
	{
		sd = srv->client_sck[i].fd;
		if (sd > 0)
		{
			red();
			printf("Shutdown client: %d\n", srv->client_sck[i].fd);
			reset();
			shutdown(sd, SHUT_WR);
			if (close(sd))
				perror("close");
			srv->client_sck[i].fd = -1;
		}
	}
	free(srv->client_sck);
	if (close(srv->master_sck))
		perror("close");
	free(*g_srv);
	printf("Quit: %d", sig);
	exit(sig);
}

/*
 * use IBM implementation (poll)
 * https://www.ibm.com/docs/en/i/7.2?topic=designs-using-poll-instead-select
 */
int main(int ac, char **av)
{
	t_srv			*srv;
	t_world_state	st;
	t_param			param;
	int				tmp_n_client_sck;
	int				end_server = 0;

	param = parse_input(ac, av);
	st = init_world(param);
	if (!st.map)
	{
		free_params(&param);
		exit(EXIT_FAILURE);
	}
	srv = init_srv(&param, &st);
	if (!srv)
		return (EXIT_FAILURE);
	g_srv = &srv;
	setup_signal();
	send_to_all_moniteur(srv, moniteur_mct(srv->world));
	yellow();
	printf("Launch srv\n");
	reset();

	tmp_n_client_sck = srv->n_client_sck;
	srv->client_sck[0].fd = srv->master_sck;
	srv->client_sck[0].events = POLLIN;
	srv->last_frame_stamp = clock();
	while (!end_server)
	{
		clock_t last_until = delta_to_clock_t(srv->param->time_delta);
		while (clock() - srv->last_frame_stamp < last_until)
		{
			if (poll(srv->client_sck, srv->n_client_sck, 0) < 0)
			{
				perror("poll");
				exit(EXIT_FAILURE);
			}
			tmp_n_client_sck = srv->n_client_sck;
			for (int i = 0; i < tmp_n_client_sck; i++)
			{
				// check if there is no action with this socket
				if (srv->client_sck[i].revents == 0 \
						|| srv->client_sck[i].revents != POLLIN)
					continue ;
				if (srv->client_sck[i].fd == srv->master_sck)
					add_client(srv);
				else
					listen_client(srv, i);
			}
		}
		game_tick(srv);
	}
	ft_quit(0);
	return (EXIT_SUCCESS);
}
