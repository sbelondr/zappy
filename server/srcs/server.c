/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:58:32 by sbelondr          #+#    #+#             */
/*   Updated: 2021/03/03 20:16:21 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_srv **g_srv = NULL;

void ft_quit(int sig)
{
	t_srv *srv = *g_srv;
	int i = -1;
	int sd;

	while (srv && ++i < MAX_CLIENT)
	{
		sd = srv->client_sck[i];
		if (sd > 0)
		{
			getpeername(sd, (struct sockaddr *)&(srv->address),
						(socklen_t *)&(srv->addrlen));
			red();
			printf("Un client s'est barre sans payer\n");
			reset();
			close(sd);
			close(srv->client_sck[i]);
			srv->client_sck[i] = 0;
		}
	}
	close(srv->master_sck);
	free(*g_srv);
	printf("Quit: %d", sig);
	exit(sig);
}

int main(void)
{
	int max_sd;
	int activity;
	fd_set readfds;
	fd_set writefds;
	t_srv *srv = init_srv();
	struct timeval timeout;

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
		// ?, timeout, wait
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
