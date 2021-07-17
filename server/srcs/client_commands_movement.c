/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_movement.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:42:39 by selver            #+#    #+#             */
/*   Updated: 2021/07/15 12:58:52 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "constants.h"

void			move_player(t_world_state *world, t_client *client, t_orientation dir);
/*
** CE FICHIER COMPORTE LES FONCTIONS DE GAMEPLAY QUI PORTE AU MOUVEMENT
*/

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
	if ((int)player->orientation < 0)
		player->orientation = 3;
	return (ft_strdup("OK"));
}
