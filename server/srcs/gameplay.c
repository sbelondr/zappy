/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <jayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 10:10:19 by jayache           #+#    #+#             */
/*   Updated: 2021/03/09 09:39:01 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <stdlib.h>

void			generate_ressource(t_world_state world)
{
	for (int y = 0; y < world.params.world_height; y++)
		for (int x = 0; x < world.params.world_width; x++)
		{
			if (x < world.params.world_width / 2)
				world.map[y][x][LINEMATE] += (rand() % 2) * 2;
			if (x > world.params.world_width / 2)
				world.map[y][x][DERAUMERE] += (rand() % 2) * 2;
			if (y < world.params.world_height / 2)
				world.map[y][x][LAMENDIANE] += (rand() % 2) * 2;
			if (y > world.params.world_height / 2)
				world.map[y][x][SIBUR] += (rand() % 2) * 2;
			world.map[y][x][PHIRAS] += (rand() % 100 < 10);
			world.map[y][x][THYSTAME] += (rand() % 100 < 5);
			if (y > world.params.world_height / 3 && y < world.params.world_height / 3 * 2 &&
					x > world.params.world_width / 3 && x < world.params.world_width / 3 * 2)
				world.map[y][x][FOOD] += (rand() % 2);
		}
}

t_world_state	init_world(t_param params)
{
	t_world_state	ret;

	ret.params = params;
	ret.client_list = NULL;
	ret.map = calloc(params.world_height, sizeof(int**));
	for (int i = 0; i < params.world_height; i++)
		ret.map[i] = calloc(params.world_width, sizeof(int*));
	for (int y = 0; y < ret.params.world_height; y++)
		for (int x = 0; x < ret.params.world_width; x++)
			ret.map[y][x] = calloc(7, sizeof(int));
	generate_ressource(ret);
	return (ret);
}

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
