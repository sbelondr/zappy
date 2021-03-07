/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <jayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 10:10:19 by jayache           #+#    #+#             */
/*   Updated: 2021/03/07 08:53:34 by jayache          ###   ########.fr       */
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

void		broadcast(t_world_state world, t_client *emitter, char *message)
{
	t_client	*current;
	int			diff_x;
	int			diff_y;
	int			direcion;

	current = world.client_list;
	while (current)
	{
		diff_x = emitter->p_x - current->p_x;
		diff_y = emitter->p_y - current->p_y;
		if (diff_x == 0 && diff_y == 0 && emitter != current) //HACK: tqnt quíl ny a pas de copie de donnees, on peut verifier l \
																egalite entre deux structs en comparant les pointeurs
		{
			direction = 0;
		}
		else if (diff_x == 0 && 
		current = current->next;
	}
}
