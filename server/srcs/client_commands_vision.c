/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_vision.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:01:04 by selver            #+#    #+#             */
/*   Updated: 2021/10/24 10:04:14 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "functions.h"
#include <stdio.h>

/*
 * Silence warning
 */
int asprintf(char **strp, const char *fmt, ...);

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
 * TODO: player number 
 */

char	*action_see_string(t_world_state *world, t_client *player)
{
	char	*ret;
	int		*items;
	int		cnt;
	int		offsetx;
	t_vector2	target;

	t_list *current = world->client_list;
	while (current)
	{
		t_client *caller = current->content;
		printf("x: %d y: %d id: %d\n", caller->p_x, caller->p_y, caller->id);
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
	offsetx = 0;
	while (offsetx <= 1)
	{
		for (int i = -offsetx; i <= offsetx; ++i)
		{
			if (player->orientation == NORTH)
				target = ft_vector2(player->p_x + 1, player->p_y - offsetx);
			else if (player->orientation == EAST)
				target = ft_vector2(player->p_x + offsetx, player->p_y + 1);
			else if (player->orientation == SOUTH)
				target = ft_vector2(player->p_x + i, player->p_y + offsetx);
			else if (player->orientation == WEST)
				target = ft_vector2(player->p_x - offsetx, player->p_y - i);
			else
				printf("ERROR: orientation: %d !E {%d, %d, %d, %d}\n", player->orientation, NORTH, EAST, SOUTH, WEST);
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
		offsetx += 1;
	}
	ret[offset - 1] = '}';
	return (ret);
}
