/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_vision.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:01:04 by selver            #+#    #+#             */
/*   Updated: 2021/07/15 14:15:28 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "functions.h"

char	*see_inventaire(t_world_state *world, t_client *player)
{
	char	*inventory;
	int		*res;
	int		error;

	(void)world;
	res = player->ressource;
	error = asprintf(&inventory,
			"{nourriture %d, sibur %d, phiras %d, linemate %d,"
			" thystame %d, lamendiane %d, deraumere %d}",
			res[6], res[2], res[4], res[0], res[5], res[3], res[1]);
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

/*
 * Donne la chaîne de charactères à retourner au client
 * PARAMS: t_world_state *world -> world state
 *			t_client playe -> Observer
 * RETURNS:	char* -> A string under the pattern {a b c, a b, c, a}
 * TODO: player number + view scale with rank 
 */

char	*action_see_string(t_world_state *world, t_client *player)
{
	char	*ret;
	int		*items;
	int		cnt;
	int		offsetx;

	offsetx = 1;
	cnt = 0;
	while (offsetx >= 0)
	{
		for (int i = -offsetx; i <= offsetx; ++i)
		{
			items = get_case(world, player->p_y + offsetx, player->p_x + i);
			cnt += quantity_of_elements(world, items);
			printf("%d ", i);
		}
		printf("\n");
		offsetx -= 1;
	}
	printf("Elements: %d\n", cnt);
	ret = ft_strnew(cnt * 15 + 2);
	ret[0] = '{';
	int offset = 1;
	offsetx = 1;
	while (offsetx >= 0)
	{
		for (int i = -offsetx; i <= offsetx; ++i)
		{
			if (player->orientation == NORTH)
				items = get_case(world, player->p_x + i, player->p_y - offsetx);
			else if (player->orientation == EAST)
				items = get_case(world, player->p_x + offsetx, player->p_y + i);
			else if (player->orientation == SOUTH)
				items = get_case(world, player->p_x + i, player->p_y + offsetx);
			else if (player->orientation == WEST)
				items = get_case(world, player->p_x - offsetx, player->p_y - i);
			else
				printf("ERROR: orientation: %d !E {%d, %d, %d, %d}\n", player->orientation, NORTH, EAST, SOUTH, WEST);
			offset += build_see_part(ret + offset, " LINEMATE", items[LINEMATE]);
			offset += build_see_part(ret + offset, " DERAUMERE", items[DERAUMERE]);
			offset += build_see_part(ret + offset, " SIBUR", items[SIBUR]);
			offset += build_see_part(ret + offset, " LAMENDIANE", items[LAMENDIANE]);
			offset += build_see_part(ret + offset, " PHIRAS", items[PHIRAS]);
			offset += build_see_part(ret + offset, " THYSTAME", items[THYSTAME]);
			offset += build_see_part(ret + offset, " FOOD", items[FOOD]);
			if (offsetx > 0)
				ret[offset++] = ',';
		}
		offsetx -= 1;
	}
	ret[offset++] = '}';
	printf("STRING vision: %s\n", ret);
	return (ret);
}
