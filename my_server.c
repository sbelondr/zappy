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


t_srv	*init_srv(void)
{
	t_srv	*srv;
	int		opt;
	int 	i = -1;

	opt = 0;
	if (!(srv = (t_srv*)malloc(sizeof(t_srv) * 1)))
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
	if (setsockopt(srv->master_sck, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0)
	{
		dprintf(STDERR_FILENO, "setsocket not respect you (again)\n");
		free(srv);
		return (NULL);
	}
	srv->address.sin_family = AF_INET;
	srv->address.sin_addr.s_addr = INADDR_ANY;
	srv->address.sin_port = htons(PORT);
	if (bind(srv->master_sck, (struct sockaddr*)&(srv->address), sizeof(srv->address)) < 0)
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


int	main(void)
{
	int	max_sd;
	int	new_socket;
	int activity, i, valread, sd;
	char buff[512];

	fd_set	readfds;
	char	*msg = "Welcome\n";
	t_srv	*srv = init_srv();

	bzero(buff, 512);
	if (!srv)
		return (EXIT_FAILURE);
	printf("Launch srv\n");
	while (1)
	{
		FD_ZERO(&readfds);
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
		// ?, timeout, wait
		activity = select(max_sd + 1, &readfds, 0, 0, 0);
		if (activity < 0)
			dprintf(STDERR_FILENO, "select error\n");
		if (FD_ISSET(srv->master_sck, &readfds))
		{
			if ((new_socket = accept(srv->master_sck, (struct sockaddr*)&(srv->address),
							(socklen_t*)&(srv->addrlen))) < 0)
			{
				dprintf(STDERR_FILENO, "La secte... socket ne t'accepte pas\n");
				return (EXIT_FAILURE);
			}
			printf("New connection: fd -> %d\n", new_socket);
			if ((int)send(new_socket, msg, strlen(msg), 0) != (int)strlen(msg))
				dprintf(STDERR_FILENO, "Le client n a pas recu le message. Je vais lui monter ses morts\n");
			i = -1;
			while (++i < MAX_CLIENT)
			{
				if (srv->client_sck[i] == 0)
				{
					srv->client_sck[i] = new_socket;
					printf("Add new client\n");
					break ;
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
					getpeername(sd, (struct sockaddr*)&(srv->address), (socklen_t*)&(srv->addrlen));
					printf("Un client s'est barre sans payer\n");
					close(sd);
					srv->client_sck[i] = 0;
				}
				else
				{
					buff[valread] = 0;
					// send(sd, buff, strlen(buff), 0);
				}
			}
		}
	}
	printf("am here\n");
	free(srv);
	return (EXIT_SUCCESS);
}
