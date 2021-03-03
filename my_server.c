/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 22:58:32 by sbelondr          #+#    #+#             */
/*   Updated: 2021/03/02 23:33:49 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <signal.h>

static t_srv	**g_srv = NULL;

void red(void)
{
	printf("\033[0;31m");
}

void blue(void)
{
	printf("\033[0;34m");
}

void yellow(void)
{
	printf("\033[0;33m");
}

void green(void)
{
	printf("\033[0;32m");
}

void reset(void)
{
	printf("\033[0m");
}

void ft_quit(int sig)
{
	t_srv *srv = *g_srv;
	int i = -1;
	int sd;

	while (srv && ++i < MAX_CLIENT)
	{
		sd = srv->client_sck[i];
		printf("%d - %d\n", srv->client_sck[i], sd);
		if (sd > 0)
		{
			getpeername(sd, (struct sockaddr *)&(srv->address), (socklen_t *)&(srv->addrlen));
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

t_srv *init_srv(void)
{
	t_srv *srv;
	int opt;
	int i = -1;

	opt = 0;
	if (!(srv = (t_srv *)malloc(sizeof(t_srv) * 1)))
	{
		dprintf(STDERR_FILENO, "Malloc error\n");
		exit(EXIT_FAILURE);
	}
	while (++i < MAX_CLIENT)
		srv->client_sck[i] = 0;
	if ((srv->master_sck = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		dprintf(STDERR_FILENO, "Socket not respect you\n");
		free(srv);
		return (NULL);
	}
	if (setsockopt(srv->master_sck, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
	{
		dprintf(STDERR_FILENO, "setsocket not respect you (again)\n");
		free(srv);
		return (NULL);
	}
	srv->address.sin_family = AF_INET;
	srv->address.sin_addr.s_addr = INADDR_ANY;
	srv->address.sin_port = htons(PORT);
	if (bind(srv->master_sck, (struct sockaddr *)&(srv->address), sizeof(srv->address)) < 0)
	{
		dprintf(STDERR_FILENO, "Meme le port ne peut pas te bind\n");
		free(srv);
		return (NULL);
	}
	if (listen(srv->master_sck, 3) < 0)
	{
		dprintf(STDERR_FILENO, "I'm not listen you because I don't give a fuck\n");
		free(srv);
		return (NULL);
	}
	srv->addrlen = sizeof(srv->address);
	return (srv);
}

int main(void)
{
	int max_sd;
	int new_socket;
	int activity, i, valread, sd;
	char buff[512];

	fd_set readfds;
	fd_set writefds;
	// char *msg = "Welcome\n";
	char *msg_receive = "Message received";
	t_srv *srv = init_srv();

	g_srv = &srv;
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, ft_quit);

	bzero(buff, 512);
	if (!srv)
		return (EXIT_FAILURE);
	yellow();
	printf("Launch srv\n");
	reset();
	struct timeval timeout;
	timeout.tv_sec = 2;
	timeout.tv_usec = 0;

	while (1)
	{
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_SET(srv->master_sck, &readfds);
		max_sd = srv->master_sck;
		i = -1;
		while (++i < MAX_CLIENT)
		{
			sd = srv->client_sck[i];
			if (sd > 0)
				FD_SET(sd, &readfds);
			// increase sd
			if (sd > max_sd)
				max_sd = sd;
		}
		// FD_ZERO(&readfds);
		// ?, timeout, wait
		activity = select(max_sd + 1, &readfds, &writefds, 0, &timeout);
		if (activity < 0)
			dprintf(STDERR_FILENO, "select error\n");
		if (activity > 0)
		{
			if (FD_ISSET(srv->master_sck, &readfds))
			{
				if ((new_socket = accept(srv->master_sck, (struct sockaddr *)&(srv->address),
										 (socklen_t *)&(srv->addrlen))) < 0)
				{
					red();
					dprintf(STDERR_FILENO, "La secte... socket ne t'accepte pas\n");
					reset();
					return (EXIT_FAILURE);
				}
				yellow();
				printf("New connection: fd -> %d\n", new_socket);
				reset();
				// if ((int)send(new_socket, msg, strlen(msg), 0) != (int)strlen(msg))
				// 	dprintf(STDERR_FILENO, "Le client n a pas recu le message. Je vais lui monter ses morts\n");
				i = -1;
				while (++i < MAX_CLIENT)
				{
					if (srv->client_sck[i] == 0)
					{
						srv->client_sck[i] = new_socket;
						yellow();
						printf("Add new client\n");
						reset();
						break;
					}
				}
			}
			i = -1;
			while (++i < MAX_CLIENT)
			{
				sd = srv->client_sck[i];
				if (FD_ISSET(sd, &readfds))
				{
					if ((valread = read(sd, buff, 1024)) == 0)
					{
						getpeername(sd, (struct sockaddr *)&(srv->address), (socklen_t *)&(srv->addrlen));
						red();
						printf("Un client s'est barre sans payer\n");
						reset();
						close(sd);
						srv->client_sck[i] = 0;
					}
					else
					{
						// read data
						buff[valread] = 0;
						green();
						printf("[%d] ->\033[0;34m %s\n", srv->client_sck[i], buff);
						reset();
						send(srv->client_sck[i], msg_receive, strlen(msg_receive), 0);
					}
				}
			}
		}
	}
	free(srv);
	return (EXIT_SUCCESS);
}
