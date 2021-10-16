/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 10:02:30 by selver            #+#    #+#             */
/*   Updated: 2021/10/16 10:16:42 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * FUNCTION TO HANDLE THE COMMAND STRUCT
 */

#include "server.h"

void append_command(t_client *client, t_command to_append)
{
	int i;

	for (i = 0; i < 10 && client->buffer[i].command != COMMAND_NONE; ++i);
	client->buffer[i] = to_append;
}

t_command new_command(t_command_type command, char *arg, int cooldown)
{
	return ((t_command){command, arg, cooldown});
}

void	shift_command(t_client *client)
{
	ft_memmove(client->buffer, client->buffer + 1, sizeof(client->buffer) * 9);
	client->buffer[9] = new_command(COMMAND_NONE, NULL, 0);
}
