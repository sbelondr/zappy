/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:57:53 by sbelondr          #+#    #+#             */
/*   Updated: 2022/04/04 11:13:50 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

#define CLIENT_VALUE(x) (t_client*)(x->content)

int	search_new_id_client(int *id_clients, int team_hard_limit)
{
	int			is_exist;
	int			i;
	int			j;
	int			client_max = team_hard_limit * 2;

	while (++i < client_max)
	{
		j = -1;
		is_exist = 0;
		while (++j < client_max)
		{
			if (id_clients[j] == i)
			{
				is_exist = 1;
				break ;
			}
		}
		if (!is_exist)
		{
			printf("%d - %d\n", i, j);
			sleep(1);
			return (i);
		}
	}
	printf("iiii -1\n");
	sleep(1);
	return (-1);
}

int	search_client_index_by_id(t_srv *srv, int id)
{
	int			i = 0;
	int			*list_id = srv->id_clients;

	while (++i < srv->n_client_sck)
	{
		if (list_id[i] == id)
		{
			//			printf("index: %d, id: %d, fd: %d\n", i, list_id[i], \
			//					srv->client_sck[i].fd);
			return (i);
		}
	}
	return (-1);
}

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

	new_sd = accept(srv->master_sck, NULL, NULL);
	if (new_sd < 0)
	{
		perror("accept");
		return (-1);
	}
	printf("New incoming connection - %d\n", new_sd);
	int	i = srv->n_client_sck;
	if (i >= (srv->world->params.allowed_clients_amount + 1))
	{
		dprintf(STDERR_FILENO, "NO MORE ROOM\n");
		return (-1);
	}

	int new_id = search_new_id_client(srv->id_clients, \
			srv->param->team_hard_limit);
	srv->client_sck[i].fd = new_sd;
	srv->id_clients[i] = new_id;
	srv->client_sck[i].events = POLLIN;
	++srv->n_client_sck;
	ft_lst_append(&srv->world->client_list, \
			ft_lstnew_no_copy(new_client(new_id), sizeof(t_client)));
	if (can_print(srv->param, LOG_CONNEXION))
	{
		yellow();
		printf("Add new client: %d\n", new_id);
		reset();
	}
	simple_send_no_free(srv, new_id, "BIENVENUE\n");
	return (1);
}
