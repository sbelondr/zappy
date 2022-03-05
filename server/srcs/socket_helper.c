/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 11:07:01 by jayache           #+#    #+#             */
/*   Updated: 2022/03/05 11:07:26 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions"

/*
 * Simplified way to call send
 * Free the message, so you need to alloc it first
 */

void simple_send(t_srv *srv, int id, char *msg)
{
	if (can_print(srv->param, LOG_SEND))
	{
		blue();
		printf("[%d] <- %s", srv->client_sck[id], msg);
		reset();
	}
	if ((int)send(srv->client_sck[id], msg, \
				strlen(msg), 0) != (int)strlen(msg))
		dprintf(STDERR_FILENO, ERROR_SEND_CLIENT, \
				srv->client_sck[id]);
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
		blue();
		printf("[%d] <- %s", srv->client_sck[id], msg);
		reset();
	}
	if ((int)send(srv->client_sck[id], msg, \
				strlen(msg), 0) != (int)strlen(msg))
		dprintf(STDERR_FILENO, ERROR_SEND_CLIENT, \
				srv->client_sck[id]);
}
