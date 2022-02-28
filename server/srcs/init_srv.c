/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_srv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:58:05 by sbelondr          #+#    #+#             */
/*   Updated: 2022/02/28 16:13:17 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

t_srv *init_srv(t_param *param, t_world_state *st)
{
	t_srv	*srv;
	int		opt;

	opt = SO_REUSEADDR | SO_DEBUG;
	if (!param)
		ft_error("No param where given to init_srv\n");
	if (!(srv = (t_srv *)malloc(sizeof(t_srv) * 1)))
	{
		dprintf(STDERR_FILENO, "Malloc error\n");
		exit(EXIT_FAILURE);
	}
	if (!(srv->client_sck = (int*)calloc(sizeof(int), param->team_hard_limit * 2))) //TODO call dedicated function
		ft_error("Can't allocate memory\n");
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
	/* setup non blocking socket */
//	if (ioctl(srv->master_sck, FIONBIO, &opt) < 0)
//	{
//		dprintf(STDERR_FILENO, "ioctl failled\n");
//		free(srv);
//		return (NULL);
//	}
	srv->address.sin_family = AF_INET;
	srv->address.sin_addr.s_addr = INADDR_ANY;
	srv->address.sin_port = htons(param->port);
	if (bind(srv->master_sck, (struct sockaddr *)&(srv->address),
			 sizeof(srv->address)) < 0)
	{
		perror("bind");
		dprintf(STDERR_FILENO, "Meme le port ne peut pas te bind\n");
		free(srv);
		return (NULL);
	}
	/* backlog (man listen):
	 * maximum length to which the queue of pending connections for sockfd may grow
	 */
	int	backlog = 32;
	if (listen(srv->master_sck, backlog) < 0)
	{
		dprintf(STDERR_FILENO, "listen failled\n");
		free(srv);
		return (NULL);
	}
	srv->addrlen = sizeof(srv->address);
	srv->param = param;
	srv->world = st;
	srv->frame_nbr = 0;
	return (srv);
}
