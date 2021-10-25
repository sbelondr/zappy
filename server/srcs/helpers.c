/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 10:50:47 by selver            #+#    #+#             */
/*   Updated: 2021/10/24 10:53:09 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
 * Simplified way to call send
 */

void simple_send(t_srv *srv, int id, char *msg)
{
	if ((int)send(srv->client_sck[id], msg, strlen(msg), 0) != (int)strlen(msg))
	{
		dprintf(STDERR_FILENO, ERROR_SEND_CLIENT, srv->client_sck[id]);
	}
}

t_client *get_current_client(t_srv *srv, int i)
{
	return (ft_lstgetbypos(srv->world->client_list, i)->content);
}

