/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_vision.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:01:04 by selver            #+#    #+#             */
/*   Updated: 2022/02/05 13:51:38 by jayache          ###   ########.fr       */
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
			res[FOOD], res[SIBUR], res[PHIRAS], res[LINEMATE],
			res[THYSTAME], res[LAMENDIANE], res[DERAUMERE]);
	if (error < 0)
		ft_error("Fatal: asprintf a retourné une erreur (" __FILE__ " !!\n");
	return (inventory);
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

t_vector2	index_to_map_vector(int index)
{
	if (index == 0) return ft_vector2(0, 0);
	if (index == 1) return ft_vector2(-1, 1);
	if (index == 2) return ft_vector2(0, 1);
	if (index == 3) return ft_vector2(1, 1);
	if (index == 4) return ft_vector2(-2, 2);
	if (index == 5) return ft_vector2(-1, 2);
	if (index == 6) return ft_vector2(0, 2);
	if (index == 7) return ft_vector2(1, 2);
	if (index == 8) return ft_vector2(2, 2);
	printf("ERROR: Index is too far!!\n");
	return ft_vector2(0, 0);
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
	int		offsetx;
	t_vector2	target;

	(void)srv;
	t_list *current = world->client_list;
	while (current)
	{
		t_client *caller = current->content;
		current = current->next;
	}
	offsetx = 1;
	cnt = 0;
	while (offsetx >= 0)
	{
		for (int i = -offsetx; i <= offsetx; ++i)
		{
			items = get_case(world, player->p_y + offsetx, player->p_x + i);
			cnt += quantity_of_elements(items);
		}
		offsetx -= 1;
	}
	const int player_level_demo = 3; //Remplacer par player->lvl quand ça sera prêt
	int number_of_cases = (1 + ((player_level_demo - 1) * 2 + 1)) / 2 * player_level_demo;
	ret = ft_strnew(cnt * 15 + number_of_cases + 5000); //nique, on devrait jamais avoir autant besoin de caractères donc pas de segfault
	ret[0] = '{';
	int offset = 1;
	for (int i = 0; i < 4; ++i) //remplacer 4 par le nombre de case au niveau
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
		int nbr = 0;
		t_client *client;
		t_list *current;
		current = world->client_list;
		while (current)
		{
			client = current->content;	
			if (client->p_x == target.x && client->p_y == target.y && client->id != player->id)
				nbr += 1;
			current = current->next;
		}
		offset += build_see_part(ret + offset, " PLAYER", nbr);
		ret[offset++] = ',';
	}
	ret[offset - 1] = '}';
	return (ret);
}
