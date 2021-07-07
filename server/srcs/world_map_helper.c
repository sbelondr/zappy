/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_map_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 09:01:14 by selver            #+#    #+#             */
/*   Updated: 2021/07/07 10:26:50 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "constants.h"

/*
 * FONCTIONS DÉDIÉES À AIDER LE TRAITEMENT DE LA CARTE
 */

/*
 * Retourne la case, avec la logique qu'un élément x ou y dépassant des limites
 * de la carte reboucle au début/fin
 * PARAMS:	t_world_state	*world	->	la carte
 *			int				x		->	la coordonnée x
 *			int				y		->	la coordonnée y
 * RETURNS: int[7] -> la case
 */

int *get_case(t_world_state *world, int x, int y)
{
	while (x < 0)
		x += world->params.world_width;
	while (y < 0)
		y += world->params.world_height;
	x %= world->params.world_width;
	y %= world->params.world_height;
	return (world->map[y][x]);
}

/*
 * Retourne le nombre d'élément sur la case
 * PARAMS:	t_world_state*	world	->	carte 
 *			int*			square	->	case
 * RETURNS: int	-> nombre d'élément
 * TODO:	prendre en compte le nombre de joueurs sur la case aussi
 */

int	quantity_of_elements(t_world_state *world, int *square)
{
	int	ret;

	ret = 0;
	for (int i = 0; i < 6; ++i)
		ret += square[i];
	return (ret);
}
