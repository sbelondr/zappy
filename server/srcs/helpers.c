/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 10:50:47 by selver            #+#    #+#             */
/*   Updated: 2022/03/11 10:14:21 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void		emergency_exit(char const *perror_prefix) //TODO: Free
{
	if (perror_prefix)
		perror(perror_prefix);
	exit(1);
}

int			use_localized_string(t_param *param)
{
	return (!(param->flags & FLAG_PEDANTIC) && (param->flags & FLAG_LOCALIZED));
}

int			is_valid_item(char const *item)
{
	return (!strcmp(item, LOCFOOD) || !strcmp(item, LOCLINEMATE)
			|| !strcmp(item, LOCDERAUMERE) || !strcmp(item, LOCSIBUR)
			|| !strcmp(item, LOCMENDIANE) || !strcmp(item, LOCPHIRAS)
			|| !strcmp(item, LOCTHYSTAME));
}

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
}
