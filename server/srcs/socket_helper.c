/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 11:07:01 by jayache           #+#    #+#             */
/*   Updated: 2022/03/24 10:01:41 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

/*
 * Simplified way to call send
 * Free the message, so you need to alloc it first
 */

void simple_send(t_srv *srv, int id, char *msg)
{
	if (can_print(srv->param, LOG_SEND))
	{
		set_color(BLUE, srv->param->flags);
		printf("[%d] <- %s", srv->client_sck[id + 1].fd, msg);
		set_color(RESET, srv->param->flags);
	}
	if ((int)send(srv->client_sck[id + 1].fd, msg, \
				strlen(msg), 0) != (int)strlen(msg))
		perror("send");
	free(msg);
}

/*
 * See: simple_send
 * Does not free msg
 */

void simple_send_no_free(t_srv *srv, int id, char const *msg)
{
	if (can_print(srv->param, LOG_SEND))
	{
		set_color(BLUE, srv->param->flags);
		printf("[%d] <- %s", srv->client_sck[id + 1].fd, msg);
		set_color(RESET, srv->param->flags);
	}
	if ((int)send(srv->client_sck[id + 1].fd, msg, \
				strlen(msg), 0) != (int)strlen(msg))
		perror("send");
}
