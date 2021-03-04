/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:58:32 by sbelondr          #+#    #+#             */
/*   Updated: 2021/03/04 10:43:39 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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

	while (srv && ++i < srv->settings_srv->max_client)
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
	ft_arraydel(&(srv->settings_srv->team));
	free(srv->settings_srv);
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
	t_settings_srv *settings_srv = ft_parse_arg_srv(av);

	(void)ac;
	if (!settings_srv)
		exit(EXIT_FAILURE);
	srv = init_srv(settings_srv);
	g_srv = &srv;
	generate_map();
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
