/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:58:11 by sbelondr          #+#    #+#             */
/*   Updated: 2021/10/16 09:35:41 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <stdio.h>
/*
** wtf genre tu lis ou tu écris 
*/

void ft_listen_srv(t_srv *srv, fd_set *readfds)
{
	char buff[BUFF_READ];
	int sd;
	int i;
	int	valread;

	i = -1;
	while (++i < srv->param->allowed_clients_amount)
	{
		sd = srv->client_sck[i];
		if (FD_ISSET(sd, readfds))
		{
			bzero(buff, BUFF_READ);
			if ((valread = read(sd, buff, BUFF_READ)) == 0)
				ft_client_exit(srv, sd, i);
			else
				ft_client_send_data(srv, buff, valread, i); //Genre ça ça veut dire que tu envoies des données du serveur au client non ????
		}
	}
}
