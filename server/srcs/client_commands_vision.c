/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_vision.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 15:01:04 by selver            #+#    #+#             */
/*   Updated: 2021/07/05 16:27:54 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

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
		offset += 9;
	}
	return (offset);
}

/*
 * Donne la chaîne de charactères à retourner au client
 * PARAMS: t_world_state *world -> world state
 *			t_client playe -> Observer
 * RETURNS:	char* -> A string under the pattern {a b c, a b, c, a}
 * TODO: player number + view scales with level
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

