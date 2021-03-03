/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:58:11 by sbelondr          #+#    #+#             */
/*   Updated: 2021/03/03 21:00:56 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void ft_listen_srv(t_srv *srv, fd_set *readfds)
{
	char buff[BUFF_READ];
	int sd;
	int i;
	int	valread;

	i = -1;
	while (++i < MAX_CLIENT)
	{
		sd = srv->client_sck[i];
		if (FD_ISSET(sd, readfds))
		{
			bzero(buff, BUFF_READ);
			if ((valread = read(sd, buff, BUFF_READ)) == 0)
				ft_client_exit(srv, sd, i);
			else
				ft_client_send_data(srv, buff, valread, i);
		}
	}
}
