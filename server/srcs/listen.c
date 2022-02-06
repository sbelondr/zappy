/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:58:11 by sbelondr          #+#    #+#             */
/*   Updated: 2022/02/06 14:14:42 by jayache          ###   ########.fr       */
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
	int i;
	int	valread;

	i = -1;
	while (++i < srv->param->team_hard_limit * 2)
	{
		if (FD_ISSET(srv->client_sck[i], readfds))
		{
			bzero(buff, BUFF_READ);
			if ((valread = read(srv->client_sck[i], buff, BUFF_READ)) == 0)
				ft_client_exit(srv, i);
			else
				ft_client_send_data(srv, buff, valread, i); //Genre ça ça veut dire que tu envoies des données du serveur au client non ????
		}
	}
}
