/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 10:02:30 by selver            #+#    #+#             */
/*   Updated: 2022/03/03 08:59:47 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * FUNCTION TO HANDLE THE COMMAND STRUCT
 */

#include "functions.h"

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
	if (client->buffer[0].arg)
		free(client->buffer[0].arg);
	ft_memcpy(client->buffer, client->buffer + 1, sizeof(t_command) * 9);
	client->buffer[9] = new_command(COMMAND_NONE, NULL, 0);
}

void clear_commands(t_client *client)
{
	for (int i = 0; i < 10; ++i)
	{
		if (client->buffer[i].arg)
			free(client->buffer[i].arg);
		client->buffer[i].arg = NULL;
	}
}
