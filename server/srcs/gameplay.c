/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <jayache@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 10:10:19 by jayache           #+#    #+#             */
/*   Updated: 2021/07/05 10:37:00 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>

/*
** Construit un élément de la chaîne de caractère de vision
** PARAMS: char* str -> le string en construction, doit avoir la bonne taille déjà allouée
**			char *name -> nom de l'élément que l'on ai en train de rajouter
**			int count -> nombre de l'élément
** RETURNS:	int -> nombre de caractères ajoutés
*/

int	build_see_part(char *str, char *name, int count)
{
	int offset;

	offset = 0;
	for (int i = 0; i < count; ++i)
	{
		ft_memmove(str + offset, name, ft_strlen(name));
		offset += 9;
	}
	return (offset);
}

/*
 * Donne la chaîne de charactères à retourner au client
 * PARAMS: t_world_state *world -> world state
 *			t_client playe -> Observer
 * RETURNS:	char* -> A string under the pattern {a b c, a b, c, a}
 * TODO: Remove excess comma + player number + view scales with level
 */
char	*action_see_string(t_world_state *world, t_client *player)
{
	char	*ret;
	int		*items;
	int		cnt;

	items = world->map[player->p_y][player->p_x];
	cnt = 9 * items[0];
	cnt += 10 * items[1];
	cnt += 6 * items[2];
	cnt += 13 * items[3];
	cnt += 7 * items[4];
	cnt += 9 * items[5];
	cnt += 5 * items[6];
	ret = ft_strnew(cnt + 2 + 7);
	ret[0] = '{';
	int offset = 1;
	offset += build_see_part(ret + offset, " LINEMATE", items[0]);
	offset += build_see_part(ret + offset, " DERAUMERE", items[1]);
	offset += build_see_part(ret + offset, " SIBUR", items[2]);
	offset += build_see_part(ret + offset, " LAMENDIANE", items[3]);
	offset += build_see_part(ret + offset, " PHIRAS", items[4]);
	offset += build_see_part(ret + offset, " THYSTAME", items[5]);
	offset += build_see_part(ret + offset, " FOOD", items[6]);
	offset += build_see_part(ret + offset, " PLAYER", 0);
	ret[offset++] = '}';
	return (ret);
}

char	*see_inventaire(t_world_state *world, t_client *player)
{
	char	*inventory;
	int		*res;
	int		error;

	(void)world;
	res = player->ressource;
	error = asprintf(&inventory,
			"{nourriture %d, sibur %d, phiras %d, linemate %d,"
			"thystame %d, lamendiane %d, deraumere %d}",
			res[6], res[2], res[4], res[0], res[5], res[3], res[1]);
	if (error < 0)
		printf("ERROR!!\n");
	return (inventory);
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

char	*avance(t_world_state *world, t_client *player)
{
	move_player(world, player, player->orientation);
	return (ft_strdup("OK"));
}

char	*turn_right(t_world_state *world, t_client *player)
{
	(void)world;
	player->orientation = (player->orientation + 1) % 4;
	return (ft_strdup("OK"));
}

char	*turn_left(t_world_state *world, t_client *player)
{
	(void)world;
	player->orientation -= 1;
	if (player->orientation < 0)
		player->orientation = 3;
	return (ft_strdup("OK"));
}
