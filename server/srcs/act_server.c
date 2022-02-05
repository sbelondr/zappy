/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:57:53 by sbelondr          #+#    #+#             */
/*   Updated: 2022/02/05 11:15:53 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "functions.h"

void ft_add_new_client(t_srv *srv, fd_set *readfds)
{
	int new_socket;

	if (FD_ISSET(srv->master_sck, readfds))
	{
		int i;
		if ((new_socket = accept(srv->master_sck,
						(struct sockaddr *)&(srv->address),
						(socklen_t *)&(srv->addrlen))) < 0)
		{
			red();
			dprintf(STDERR_FILENO, "La secte... socket ne t'accepte pas\n");
			reset();
			return; // (EXIT_FAILURE);
		}
		yellow();
		printf("New connection: fd -> %d\n", new_socket);
		reset();
		i = -1;
		while (++i < 2000) //TODO: change that
		{
			if (srv->client_sck[i] == 0)
			{
				srv->client_sck[i] = new_socket;
				yellow();
				printf("Add new client: %d\n", i);
				reset();
				simple_send(srv, i, ft_strdup("BIENVENUE\n"));
				ft_lst_append(&srv->world->client_list, ft_lstnew_no_copy(new_client(i), sizeof(t_client)));
				break;
			}
		}
		//loops through eggs
	}
}

int ft_set_max_sd(t_srv *srv, fd_set *readfds)
{
	int sd, max_sd;
	int i;

	max_sd = srv->master_sck;
	i = -1;
	while (++i < 2000)
	{
		sd = srv->client_sck[i];
		if (sd > 0)
			FD_SET(sd, readfds);
		// increase sd
		if (sd > max_sd)
			max_sd = sd;
	}
	return (max_sd);
}
