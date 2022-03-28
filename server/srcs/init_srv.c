/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_srv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:58:05 by sbelondr          #+#    #+#             */
/*   Updated: 2022/03/28 23:06:21 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	emergency_free_srv(t_srv *srv, t_param *param, char *perror_string)
{
	if (perror_string)
		perror(perror_string);
	if (srv)
	{
		if (srv->client_sck)
			free(srv->client_sck);
		free(srv);
	}
	if (param)
	{
		free_params(param);
	}
	exit(EXIT_FAILURE);
}

t_srv *init_srv(t_param *param, t_world_state *st)
{
	t_srv	*srv;
	int		opt;

	opt = SO_REUSEADDR | SO_DEBUG;
	if (!param)
		ft_error("No param where given to init_srv\n");
	if (!(srv = (t_srv *)calloc(sizeof(t_srv), 1)))
		emergency_free_srv(srv, param, "calloc");
	if (!(srv->client_sck = (struct pollfd*)calloc(sizeof(struct pollfd), param->team_hard_limit * 2)))
		emergency_free_srv(srv, param, "calloc");
	if ((srv->master_sck = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		emergency_free_srv(srv, param, "socket");
	if (setsockopt(srv->master_sck, SOL_SOCKET, SO_REUSEADDR,
				   (char *)&opt, sizeof(opt)) < 0)
		emergency_free_srv(srv, param, "setsockopt");
	srv->address.sin_family = AF_INET;
	srv->address.sin_addr.s_addr = INADDR_ANY;
	srv->address.sin_port = htons(param->port);
	if (bind(srv->master_sck, (struct sockaddr *)&(srv->address),
			 sizeof(srv->address)) < 0)
		emergency_free_srv(srv, param, "bind");
	/* backlog (man listen):
	 * maximum length to which the queue of pending connections for sockfd may grow
	 */
	int	backlog = 32;
	if (listen(srv->master_sck, backlog) < 0)
		emergency_free_srv(srv, param, "listen");
	srv->addrlen = sizeof(srv->address);
	srv->param = param;
	srv->world = st;
	srv->frame_nbr = 0;
	srv->n_client_sck = param->allowed_clients_amount + 1;
	return (srv);
}
