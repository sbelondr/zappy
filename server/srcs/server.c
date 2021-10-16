/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:58:32 by sbelondr          #+#    #+#             */
/*   Updated: 2021/10/16 10:48:08 by selver           ###   ########.fr       */
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
	t_world_state st;
	t_param param = parse_input(ac, av);

	st = init_world(param);
	srv = init_srv(&param, &st);
	if (!srv)
		return (EXIT_FAILURE);
	g_srv = &srv;
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
		while (timeout.tv_sec > 0 || timeout.tv_usec > 0) 
		{
			activity = select(max_sd + 1, &readfds, &writefds, 0, &timeout);
			if (activity < 0)
				dprintf(STDERR_FILENO, "select error\n");
			if (activity > 0)
			{
				ft_add_new_client(srv, &readfds);
				ft_listen_srv(srv, &readfds);
			}
		}
		timeout.tv_sec = 2;
		for (int i = 0; i < param.allowed_clients_amount; ++i)
		{
			t_list *current = ft_lstgetbypos(st.client_list, i);
			t_client *client;	
			if (!current)
				continue;
			client = current->content;
			if (client->buffer[0].cooldown > 0)
				client->buffer[0].cooldown -= 1;
			else
			{
				if (client->buffer[0].command != COMMAND_NONE)
				{
					printf("VALID %s", client->buffer[0].arg);
					t_game_action act = get_action_from_enum(client->buffer[0].command);
					char *msg = act(srv->world, client);
					send(srv->client_sck[i], msg, ft_strlen(msg), 0);
					shift_command(client);
				}
			}
		}
		printf("TEST\n");
	}
	free(srv);
	return (EXIT_SUCCESS);
}
