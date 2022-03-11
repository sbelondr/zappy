/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:57:53 by sbelondr          #+#    #+#             */
/*   Updated: 2022/03/11 14:01:28 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

/*
 * add new client
 * Args:
 *	srv: struct server
 * Return:
 *	if client is accept
 */
int	add_client(t_srv *srv, int end_server)
{
	int	new_sd = 0;

	new_sd = accept(srv->master_sck, NULL, NULL) ;
	//		(struct sockaddr *)&(srv->address), \
	(socklen_t *)&(srv->addrlen));
	if (new_sd < 0)
	{
		perror(" accept() failed");
		end_server = 1;
		return (end_server);
	}
	printf("New incoming connection - %d\n", new_sd);
	srv->client_sck[srv->n_client_sck].fd = new_sd;
	srv->client_sck[srv->n_client_sck].events = POLLIN;
	if (can_print(srv->param, LOG_CONNEXION))
	{
		yellow();
		printf("Add new client: %d\n", srv->n_client_sck);
		reset();
	}
	simple_send(srv, srv->n_client_sck, ft_strdup("BIENVENUE\n"));
	ft_lst_append(&srv->world->client_list, \
			ft_lstnew_no_copy(new_client(srv->n_client_sck), \
				sizeof(t_client)));
	//		new_sd = -1;
	++srv->n_client_sck;
	return (end_server);
}
