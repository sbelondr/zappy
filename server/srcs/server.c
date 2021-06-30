/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:58:32 by sbelondr          #+#    #+#             */
/*   Updated: 2021/06/30 11:22:21 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "struct.h"
#include "functions.h"

static t_srv **g_srv = NULL;

void	ft_arraydel(char ***line)
{
	int	i;

	i = -1;
	if (*line)
	{
		while ((*line)[++i])
			free((*line)[i]);
		free(*line);
		*line = NULL;
	}
}

void ft_quit(int sig)
{
	t_srv *srv = *g_srv;
	int i = -1;
	int sd;

	while (srv && ++i < srv->param->allowed_clients_amount)
	{
		sd = srv->client_sck[i];
		if (sd > 0)
		{
			red();
			printf("Un client s'est barre sans payer\n");
			reset();
			shutdown(sd, SHUT_WR);
			if (close(sd))
				perror("close");
			srv->client_sck[i] = 0;
		}
	}
	free(srv->client_sck);
	if (close(srv->master_sck))
		perror("close");
	free(*g_srv);
	printf("Quit: %d", sig);
	exit(sig);
}

int main(int ac, char **av)
{
	int max_sd;
	int activity;
	fd_set readfds;
	fd_set writefds;
	t_srv *srv;
	struct timeval timeout;
	t_param param = parse_input(ac, av);
	t_world_state st;
	st = init_world(param);

	srv = init_srv(&param, &st);
	g_srv = &srv;
	if (!srv)
		return (EXIT_FAILURE);
	reset_term();
	yellow();
	printf("Launch srv\n");
	reset();
	timeout.tv_sec = 2;
	timeout.tv_usec = 0;
	while (1)
	{
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_SET(srv->master_sck, &readfds);
		max_sd = ft_set_max_sd(srv, &readfds);
		activity = select(max_sd + 1, &readfds, &writefds, 0, &timeout);
		if (activity < 0)
			dprintf(STDERR_FILENO, "select error\n");
		if (activity > 0)
		{
			ft_add_new_client(srv, &readfds);
			ft_listen_srv(srv, &readfds);
		}
	}
	free(srv);
	return (EXIT_SUCCESS);
}
