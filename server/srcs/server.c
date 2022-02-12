/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:58:32 by sbelondr          #+#    #+#             */
/*   Updated: 2022/02/11 12:41:51 by sbelondr         ###   ########.fr       */
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
	printf("Kill all clients\n");
	t_srv *srv = *g_srv;
	int i = -1;
	int sd;

	while (srv && ++i < srv->param->allowed_clients_amount)
	{
		sd = srv->client_sck[i];
		if (sd > 0)
		{
			red();
			printf("Shutdown client: %d\n", srv->client_sck[i]);
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
	int				max_sd;
	int				activity;
	fd_set			readfds;
	fd_set			writefds;
	t_srv			*srv;
	struct timeval	timeout;
	t_world_state	st;
	t_param			param;

	param = parse_input(ac, av);
	st = init_world(param);
	srv = init_srv(&param, &st);
	if (!srv)
		return (EXIT_FAILURE);
	g_srv = &srv;
	reset_term();
	yellow();
	printf("Launch srv\n");
	reset();
	timeout = delta_to_time(param.time_delta);
	while (1)
	{
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_SET(srv->master_sck, &readfds);
		max_sd = ft_set_max_sd(srv, &readfds);
		while (timeout.tv_sec > 0 || timeout.tv_usec > 0) 
		{
			activity = select(max_sd + 1, &readfds, &writefds, 0, &timeout);
			// activity < 0 -> error socket
			// activity > 0 -> nouvelle connection est detecte ou nouveau message recu
			// activity = 0 -> rien ne se passe
			if (activity > 0) //d'après le man ça arrive tout le temps...
				// le man a tort regarde le commentaire du haut
			{
				ft_add_new_client(srv, &readfds); //ALORS PK CA // cherche si il a recu une nouvelle connexion
				ft_listen_srv(srv, &readfds);
			}

		}
		timeout = delta_to_time(param.time_delta);
		game_tick(srv);
	}
	ft_quit(0);
	return (EXIT_SUCCESS);
}
