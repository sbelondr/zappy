/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 10:50:47 by selver            #+#    #+#             */
/*   Updated: 2021/10/28 10:00:25 by selver           ###   ########.fr       */
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
	free(msg);
}

t_client *get_current_client(t_srv *srv, int i)
{
	return (ft_lstgetbypos(srv->world->client_list, i)->content);
}

t_client *get_client_by_id(t_srv *srv, int id)
{
	t_list	*current;

	current = srv->world->client_list;
	while (current)
	{
		if (((t_client*)current->content)->id == id)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

t_egg	*get_egg_by_id(t_world_state *world, int id)
{
	t_list	*current;

	current = world->egg_list;
	while (current)
	{
		if (((t_egg*)current->content)->id == id)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}
