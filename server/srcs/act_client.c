/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:57:42 by sbelondr          #+#    #+#             */
/*   Updated: 2021/03/03 20:57:44 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void ft_client_exit(t_srv *srv, int sd, int i)
{
	getpeername(sd, (struct sockaddr *)&(srv->address),
				(socklen_t *)&(srv->addrlen));
	red();
	printf("Le client %d s'est barre sans payer\n", srv->client_sck[i]);
	reset();
	close(sd);
	srv->client_sck[i] = 0;
}

void ft_client_send_data(t_srv *srv, char *buff, int valread, int i)
{
	char *msg_receive = "Message received";

	buff[valread] = 0;
	green();
	printf("[%d] ->\033[0;34m %s\n", srv->client_sck[i], buff);
	reset();
	if ((int)send(srv->client_sck[i], msg_receive,
		 strlen(msg_receive), 0) != (int)strlen(msg_receive))
			dprintf(STDERR_FILENO, "Le client %d n a pas recu le message. Je vais lui monter ses morts\n", srv->client_sck[i]);
}
