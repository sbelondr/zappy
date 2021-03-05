/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 10:26:01 by sbelondr          #+#    #+#             */
/*   Updated: 2021/03/04 11:24:00 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char	*ft_case_ressources(int x, int y)
{

}

/*
enum	e_ressources {
	LINEMATE,
	DERAUMERE,
	SIBUR,
	LAMENDIANE,
	PHIRAS,
	THYSTAME,
	FOOD
}
*/

t_map	generate_map(void)
{
	t_map	map;
	int	x = 100;
	int y = 100;
	int	i = -1;
	int	j;

	srand(time(NULL));
	if (!(map.map_case = (t_case_map**)malloc(sizeof(t_case_map*) * y)))
		return (map);
	while (++i < y)
	{
		if (!(map.map_case[i] = (t_case_map*)malloc(sizeof(t_case_map) * x)))
			ft_quit(5);
		j = -1;
		while (++j < x)
		{
			map.map_case[i][j].ress[LINEMATE] = rand() % 2;
			map.map_case[i][j].ress[DERAUMERE] = rand() % 2;
			map.map_case[i][j].ress[SIBUR] = rand() % 2;
			map.map_case[i][j].ress[LAMENDIANE] = rand() % 2;
			map.map_case[i][j].ress[PHIRAS] = rand() % 2;
			map.map_case[i][j].ress[THYSTAME] = rand() % 2;
			map.map_case[i][j].ress[FOOD] = rand() % 2;
		}
	}

/*	
	printf("%d %d %d %d %d %d %d\n", map.map_case[10][10].ress[LINEMATE],
			map.map_case[10][10].ress[DERAUMERE],
			map.map_case[10][10].ress[SIBUR],
			map.map_case[10][10].ress[LAMENDIANE],
			map.map_case[10][10].ress[PHIRAS],
			map.map_case[10][10].ress[THYSTAME],
			map.map_case[10][10].ress[FOOD]);
*/	
	return (map);
}
