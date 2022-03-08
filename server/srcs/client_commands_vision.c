/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_vision.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:01:04 by selver            #+#    #+#             */
/*   Updated: 2022/03/08 10:15:46 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "functions.h"
#include <stdio.h>

/*
 * Silence warning
 */
int asprintf(char **strp, const char *fmt, ...);

char	*see_inventaire(t_srv *srv,t_world_state *world, t_client *player)
{
	char	*inventory;
	int		*res;
	int		error;

	(void)world;
	(void)srv;
	res = player->ressource;
	error = asprintf(&inventory,
			"{nourriture %d, sibur %d, phiras %d, linemate %d,"
			" thystame %d, lamendiane %d, deraumere %d}",
			res[FOOD] * 126 + player->hunger, res[SIBUR], res[PHIRAS], res[LINEMATE],
			res[THYSTAME], res[LAMENDIANE], res[DERAUMERE]);
	if (error < 0)
		ft_error("Fatal: asprintf a retourné une erreur (" __FILE__ " !!\n");
	return (inventory);
}

t_vector2	index_to_map_vector(int index)
{
	t_vector2	ret;
	int			limit;

	limit = 1;
	ret = ft_vector2(0, 0);
	for (int i = 0; i < index; ++i)
	{
		ret.x++;
		if (ret.x >= limit)
		{
			ret.x *= -1;
			ret.y++;
			limit++;
		}
	}
	return (ret);
}

/*
 ** Construit un élément de la chaîne de caractère de vision
 ** PARAMS: char* str -> le string en construction, doit avoir la bonne taille déjà allouée
 **			char *name -> nom de l'élément que l'on ai en train de rajouter
 **			int count -> nombre de l'élément
 ** RETURNS:	int -> nombre de caractères ajoutés
 */

static int	build_see_part(char *str, char *name, int count)
{
	int offset;

	offset = 0;
	for (int i = 0; i < count; ++i)
	{
		ft_memmove(str + offset, name, ft_strlen(name));
		offset += ft_strlen(name);
	}
	return (offset);
}

static int	player_on_position(t_world_state *world, t_vector2 pos)
{
	t_client	*client;
	t_list		*current;
	int			acc;

	acc = 0;
	current = world->client_list;
	while (current)
	{
		client = current->content;	
		if (client->p_x == pos.x && client->p_y == pos.y)
			acc += 1;
		current = current->next;
	}
	return (acc);
}

//Gives the number of cases covered by the vision
static int	vision_range(int level)
{
	return ((int)(((level + 1) / 2.0) * (2 + level * 2)));
}

static int	size_of_string(t_world_state *world, t_client *player)
{
	int			cnt;
	int			case_nbr;
	int			*items;
	t_vector2	target;

	cnt = 0;
	case_nbr = vision_range(player->lvl);
	for (int i = 0; i < case_nbr; ++i) 
	{
		target = index_to_map_vector(i);
		target = rotate_vector(target, player->orientation);
		target.x += player->p_x;
		target.y += player->p_y;
		items = get_case(world, target.x, target.y); 
		cnt += items[LINEMATE] * strlen(" LINEMATE");
		cnt += items[DERAUMERE] * strlen(" DERAUMERE");
		cnt += items[SIBUR] * strlen(" SIBUR");
		cnt += items[LAMENDIANE] * strlen(" LAMENDIANE");
		cnt += items[PHIRAS] * strlen(" PHIRAS");
		cnt += items[THYSTAME] * strlen(" THYSTAME");
		cnt += items[FOOD] * strlen(" FOOD");
		cnt += player_on_position(world, target) * strlen(" PLAYER");
	}
	cnt += case_nbr + 4;
	return (cnt);
}

/*
 * Donne la chaîne de charactères à retourner au client
 * PARAMS: t_world_state *world -> world state
 *			t_client playe -> Observer
 * RETURNS:	char* -> A string under the pattern {a b c, a b, c, a}
 * TODO: VIEW SCALES WITH LEVEL 
 */

char	*action_see_string(t_srv *srv,t_world_state *world, t_client *player)
{
	char	*ret;
	int		*items;
	int		cnt;
	int		case_nbr;
	int		offset;
	t_vector2	target;
	(void)srv;

	cnt = 0;
	case_nbr = vision_range(player->lvl);
	cnt = size_of_string(world, player);
	ret = ft_strnew(cnt);
	ret[0] = '{';
	offset = 1;
	for (int i = 0; i < case_nbr; ++i)
	{
		target = index_to_map_vector(i);
		target = rotate_vector(target, player->orientation);
		target.x += player->p_x;
		target.y += player->p_y;
		items = get_case(world, target.x, target.y); 
		offset += build_see_part(ret + offset, " LINEMATE", items[LINEMATE]);
		offset += build_see_part(ret + offset, " DERAUMERE", items[DERAUMERE]);
		offset += build_see_part(ret + offset, " SIBUR", items[SIBUR]);
		offset += build_see_part(ret + offset, " LAMENDIANE", items[LAMENDIANE]);
		offset += build_see_part(ret + offset, " PHIRAS", items[PHIRAS]);
		offset += build_see_part(ret + offset, " THYSTAME", items[THYSTAME]);
		offset += build_see_part(ret + offset, " FOOD", items[FOOD]);
		offset += build_see_part(ret + offset, " PLAYER", player_on_position(world, target));
		ret[offset++] = ',';
	}
	ret[offset - 1] = '}';
	ret[offset++] = '\n';
	return (ret);
}
