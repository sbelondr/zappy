/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_tick.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:34:19 by selver            #+#    #+#             */
/*   Updated: 2021/10/20 10:57:32 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	treat_command(t_srv *srv, t_client *client, int client_id)
{
	char *msg;
	size_t ret;

	t_game_action act = get_action_from_enum(client->buffer[0].command);
	msg = act(srv->world, client);
	printf("[%d] <- %s\n", client_id, msg);
	ret = send(srv->client_sck[client_id], msg, ft_strlen(msg), MSG_DONTWAIT);
	if (ret != ft_strlen(msg))
	{
		printf("ERROR!! send n'a pas tout envoyé");
	}
	shift_command(client);
}

void	game_tick(t_srv *srv)
{
	t_list		*current;
	t_client	*client;
	int			i;

	i = 0;
	current = srv->world->client_list;
	while (current)
	{
		client = current->content;
		if (client->buffer[0].cooldown > 0)
			client->buffer[0].cooldown -= 1;
		else
		{
			if (client->buffer[0].command != COMMAND_NONE)
			{
				treat_command(srv, client, i);
			}
		}
		current = current->next;
		++i;
	}
}
