/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <jayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 10:10:19 by jayache           #+#    #+#             */
/*   Updated: 2021/07/13 15:06:36 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "constants.h"
#include "functions.h"
#include <stdlib.h>
#include <stdio.h>


/*
 * Donne la direction du broadcast pour une paire de joueur donnée
 * PARAMS:	t_world_state *world -> world state	
 *			t_client *emitter -> The client who's speaking
 *			t_client *recepter -> The client that's listening
 * RETURNS:	int	-> The num of the case giving the direction of the ray
 * TODO: Does not take into account the recepter orientation
 */
int		broadcast(t_world_state *world, t_client *emitter, t_client *recepter)
{
	int			diff_x;
	int			diff_y;
	int			direction;

	diff_x = emitter->p_x - recepter->p_x;
	if (abs(diff_x) > world->params.world_width / 2)
		diff_x *= -1;
	if (abs(diff_y) > world->params.world_height / 2)
		diff_y *= -1;
	diff_y = emitter->p_y - recepter->p_y;
	if (diff_x == 0 && diff_y == 0 && emitter->id != recepter->id) 
	{
		direction = 0;
	}
	else if (diff_x == 0 && diff_y < 0)
		direction = 1;
	else if (diff_x == 0 && diff_y > 0)
		direction = 2;
	else if (diff_x < 0 && diff_y == 0)
		direction = 3;
	else if (diff_x > 0 && diff_y == 0)
		direction = 4;
	else if (diff_x > 0 && diff_y > 0)
		direction = 5;
	else if (diff_x < 0 && diff_y < 0)
		direction = 6;
	else if (diff_x < 0 && diff_y < 0)
		direction = 7;
	else if (diff_x < 0 && diff_y > 0)
		direction = 8;
	return (direction);
}

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
	if (dir == WEST)
	{
		target->p_x -= 1;
		if (target->p_x < 0)
			target->p_x = world->params.world_width - 1;
	}
}

int		attempt_take_item(const char *name, int *quant, int *inv, char *arg)
{
	if (ft_strequ(arg, name) && *quant > 0)
	{
		--*quant;
		++*inv;
		return (1);
	}
	return (0);
}

char	*pickup_item(t_world_state *world, t_client *player)
{
	char	*arg;
	int		*square;
	int		success;

	success = 0;
	square = get_case(world, player->p_x, player->p_y);
	printf("Player: %d %d case: %d %d %d %d\n", player->p_x, player->p_y, square[SIBUR], square[LINEMATE], square[LAMENDIANE], square[FOOD]);
	arg = player->buffer[0].arg;
	success |= attempt_take_item("SIBUR", &(square[SIBUR]), &player->ressource[SIBUR], arg);
	success |= attempt_take_item("LAMENDIANE", &square[LAMENDIANE], &player->ressource[LAMENDIANE], arg);
	success |= attempt_take_item("FOOD", &square[FOOD], &player->ressource[FOOD], arg);
	success |= attempt_take_item("LINEMATE", &(square[LINEMATE]), &player->ressource[LINEMATE], arg);
	success |= attempt_take_item("THYSTAME", &square[THYSTAME], &player->ressource[THYSTAME], arg);
	return (ft_strdup(success ? "OK" : "KO"));
}
