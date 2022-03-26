/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:57:53 by sbelondr          #+#    #+#             */
/*   Updated: 2022/03/26 10:44:08 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

/*
 * add new client
 * Args:
 *	srv: struct server
 *	end_server: check error with accept
 * Return:
 *	if error with the accept call: return -1
 */
int	add_client(t_srv *srv)
{
	int		new_sd = 0;
	char	found = 0;

	new_sd = accept(srv->master_sck, NULL, NULL);
	if (new_sd < 0)
	{
		perror("accept");
		return (-1);
	}
	printf("New incoming connection - %d\n", new_sd);
	for (int i = 1; i < srv->n_client_sck + 2; ++i)
	{
		if (srv->client_sck[i].fd == 0)
		{
			srv->client_sck[i].fd = new_sd;
			srv->client_sck[i].events = POLLIN;
			ft_lst_append(&srv->world->client_list, \
					ft_lstnew_no_copy(new_client(i - 1), \
						sizeof(t_client)));
			found = 1;
			if (can_print(srv->param, LOG_CONNEXION))
			{
				yellow();
				printf("Add new client: %d\n", i - 1);
				reset();
			}
			simple_send_no_free(srv, i - 1, "BIENVENUE\n");
			break ;
		}
		else
			printf("%d\n", srv->client_sck[i].fd);
	}
	if (!found)
		printf("NO MORE ROOM\n");
	++srv->n_client_sck;
	return (1);
}
