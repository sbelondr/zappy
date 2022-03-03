/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 10:50:47 by selver            #+#    #+#             */
/*   Updated: 2022/03/03 09:00:06 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

t_vector2	rotate_vector(t_vector2 vec, int direction)
{
	int	ca;
	int	sa;

	if (direction == NORTH)
	{
		ca = 1;
		sa = 0;
	}
	else if (direction == EAST)
	{
		ca = 0;
		sa = 1;
	}
	else if (direction == SOUTH)
	{
		ca = -1;
		sa = 0;
	}
	else if (direction == WEST)
	{
		ca = 0;
		sa = -1;
	}
	return (ft_vector2(ca * vec.x - sa * vec.y, sa * vec.x + ca * vec.y));
}

//Returns an array of string, with check to ensure it has expected elements
//If it is impossible, returns NULL
char	**split_args(char *str, int expected)
{
	int		cnt;
	char	**ret;

	cnt = 0;
	for (int i = 0; str[i]; ++i)
		cnt += (str[i] == ' ');
	if (cnt != expected)
	{
		return (NULL);
	}
	ret = ft_strsplit(str, ' ');
	if (!ret)
		return (NULL);
	for (int i = 0; i < expected + 1; ++i)
	{
		if (!ret[i])
		{
			//TODO: free
			return (NULL);
		}
	}
	return (ret);
}

/*
 * Simplified way to call send
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

t_team	*get_team_by_name(t_world_state *world, char *team_name)
{
	t_list	*current;
	t_team	*team;

	current = world->params.team_list;
	while (current)
	{
		team = current->content;
		if (!strcmp(team_name, team->team_name))
			return (team);
		current = current->next;
	}
	return (NULL);
}

int		can_print(t_param *param, t_logtype log_level)
{
	return (param->allowed_logs & log_level);
	if (log_level == LOG_TICK)
		return (param->flags & FLAG_TICK);
	return !(param->flags & FLAG_SILENT);
}
