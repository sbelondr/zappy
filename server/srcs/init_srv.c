/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_srv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:58:05 by sbelondr          #+#    #+#             */
/*   Updated: 2021/03/04 11:20:29 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_srv *init_srv(t_settings_srv *settings_srv, t_map map)
{
	t_srv	*srv;
	int		opt;
	int		i = -1;

	opt = SO_REUSEADDR | SO_DEBUG;
	if (!(srv = (t_srv *)malloc(sizeof(t_srv) * 1)))
	{
		dprintf(STDERR_FILENO, "Malloc error\n");
		exit(EXIT_FAILURE);
	}
	if (!(srv->client_sck = (int*)malloc(sizeof(int) * (settings_srv->max_client + 1))))
		return (NULL);
	while (++i < settings_srv->max_client)
		srv->client_sck[i] = 0;
	if ((srv->master_sck = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		dprintf(STDERR_FILENO, "Socket not respect you\n");
		free(srv);
		return (NULL);
	}
	if (setsockopt(srv->master_sck, SOL_SOCKET, SO_REUSEADDR,
				   (char *)&opt, sizeof(opt)) < 0)
	{
		dprintf(STDERR_FILENO, "setsocket not respect you (again)\n");
		free(srv);
		return (NULL);
	}
	srv->address.sin_family = AF_INET;
	srv->address.sin_addr.s_addr = INADDR_ANY;
	srv->address.sin_port = htons(settings_srv->port);
	if (bind(srv->master_sck, (struct sockaddr *)&(srv->address),
			 sizeof(srv->address)) < 0)
	{
		perror("bind");
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
	srv->settings_srv = settings_srv;
	srv->map = map;
	return (srv);
}
