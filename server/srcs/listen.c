/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:58:11 by sbelondr          #+#    #+#             */
/*   Updated: 2022/03/26 11:07:08 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <stdio.h>

#define SIZE_BUF 2048

/*
 * listen message receive
 */
void listen_client(t_srv *srv, int index)
{
	char	buffer[SIZE_BUF];
	int		close_conn = 0;
	int		len_read = 0;

	bzero(buffer, SIZE_BUF);
	len_read = recv(srv->client_sck[index].fd, buffer, SIZE_BUF, 0);
	if (len_read > 0)
		client_sent_data(srv, buffer, len_read, index); 
	else if (len_read < 0)
	{
		perror("recv");
		close_conn = 1;
	}
	else if (len_read == 0)
	{
		printf("Connection closed: %d\n", index);
		close_conn = 1;
	}
	if (close_conn)
		client_exit(srv, index - 1);
}
