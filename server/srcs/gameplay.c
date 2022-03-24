/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <jayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 10:10:19 by jayache           #+#    #+#             */
/*   Updated: 2022/03/24 09:15:25 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "constants.h"
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>
/*
** MOVE A PLAYER IN A DIRECTION, TAKING WORLD LIMITS INTO ACCOUNT
*/

void	move_player(t_world_state *world, t_client *target, t_orientation dir)
{
	if (dir == NORTH)
	{
		target->p_y -= 1;
		if (target->p_y < 0)
			target->p_y = world->params.world_height - 1;
	}
	else if (dir == SOUTH)
	{
		target->p_y = (target->p_y + 1) % world->params.world_height;
	}
	else if (dir == EAST)
	{
		target->p_x = (target->p_x + 1) % world->params.world_width;
	}
	else if (dir == WEST)
	{
		target->p_x -= 1;
		if (target->p_x < 0)
			target->p_x = world->params.world_width - 1;
	}
	else
	{
		printf("ERROR: move_player!! dir = %d player = %d\n", dir, target->id);
	}
}

