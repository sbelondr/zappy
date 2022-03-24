/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:57:53 by sbelondr          #+#    #+#             */
/*   Updated: 2022/03/24 09:08:56 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

/*
 * add new client
 * Args:
 *	srv: struct server
 *	end_server: check error with accept
 * Return:
 *	if error with the accept call: return 1
 */
int	add_client(t_srv *srv)
{
	int	new_sd = 0;

	new_sd = accept(srv->master_sck, NULL, NULL);
	if (new_sd < 0)
	{
		perror(" accept() failed");
		return (-1);
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
	++srv->n_client_sck;
	return (1);
}
