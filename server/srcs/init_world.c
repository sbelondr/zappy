/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:27:26 by selver            #+#    #+#             */
/*   Updated: 2022/03/15 10:17:48 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void			generate_ressource_uniform(t_world_state world)
{
	for (int y = 0; y < world.params.world_height; y++)
		for (int x = 0; x < world.params.world_width; x++)
		{
			world.map[y][x][LINEMATE] += (rand() % 2) * 2;
			world.map[y][x][DERAUMERE] += (rand() % 2) * 2;
			world.map[y][x][MENDIANE] += (rand() % 2) * 2;
			world.map[y][x][SIBUR] += (rand() % 2) * 2;
			world.map[y][x][PHIRAS] += (rand() % 2) * 2;
			world.map[y][x][THYSTAME] += (rand() % 2) * 2;
			world.map[y][x][FOOD] += (rand() % 2) * 4;
		}
}

void			generate_ressource_standard(t_world_state world)
{
	for (int y = 0; y < world.params.world_height; y++)
		for (int x = 0; x < world.params.world_width; x++)
		{
			if (x < world.params.world_width / 2)
				world.map[y][x][LINEMATE] += (rand() % 2) * 2;
			if (x > world.params.world_width / 2)
				world.map[y][x][DERAUMERE] += (rand() % 2) * 2;
			if (y < world.params.world_height / 2)
				world.map[y][x][MENDIANE] += (rand() % 2) * 2;
			if (y > world.params.world_height / 2)
				world.map[y][x][SIBUR] += (rand() % 2) * 2;
			world.map[y][x][PHIRAS] += (rand() % 100 < 10);
			world.map[y][x][THYSTAME] += (rand() % 100 < 5);
			if (y > world.params.world_height / 3 && y < world.params.world_height / 3 * 2 &&
					x > world.params.world_width / 3 && x < world.params.world_width / 3 * 2)
				world.map[y][x][FOOD] += (rand() % 2 || rand() % 2) * 2;
			else
				world.map[y][x][FOOD] += (rand() % 3);
		}
}

void			free_world_state(t_world_state *to_free)
{
	if (to_free->map)
	{
		for (int  i = 0; i < to_free->params.world_height; i++)
		{
			if (to_free->map[i])
			{
				for (int x = 0; x < to_free->params.world_width; x++)
					if (to_free->map[i][x])
					{
						free(to_free->map[i][x]);
						to_free->map[i][x] = NULL;
					}
				free(to_free->map[i]);
				to_free->map[i] = NULL;
			}
		}
		free(to_free->map);
		to_free->map = NULL;
	}
}

t_world_state	free_and_quit(t_world_state ret, char const *error_message)
{
	if (error_message)
		perror(error_message);
	free_world_state(&ret);
	return (ret);
}

t_world_state	init_world(t_param params)
{
	t_world_state	ret;

	ret.params = params;
	ret.client_list = NULL;
	ret.egg_list = NULL;
	if (!(ret.map = calloc(params.world_height, sizeof(int**))))
	{
		return (free_and_quit(ret, "malloc: "));
	}
	for (int i = 0; i < params.world_height; i++)
		if (!(ret.map[i] = calloc(params.world_width, sizeof(int*))))
		{
			return (free_and_quit(ret, "malloc: "));
		}
	for (int y = 0; y < ret.params.world_height; y++)
		for (int x = 0; x < ret.params.world_width; x++)
			if (!(ret.map[y][x] = calloc(7, sizeof(int))))
			{
				return (free_and_quit(ret, "malloc: "));
			}
	params.generate_function(ret);
	return (ret);
}
