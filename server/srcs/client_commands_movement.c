/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_movement.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:42:39 by selver            #+#    #+#             */
/*   Updated: 2021/10/28 10:41:32 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	move_player(t_world_state *world, t_client *client, t_orientation dir);
/*
** CE FICHIER COMPORTE LES FONCTIONS DE GAMEPLAY QUI PORTE AU MOUVEMENT
*/

char	*avance(t_srv *srv, t_world_state *world, t_client *player)
{
	move_player(world, player, player->orientation);
	send_to_all_moniteur(srv, moniteur_ppo(player));
	return (ft_strdup("OK\n"));
}

char	*turn_right(t_srv *srv, t_world_state *world, t_client *player)
{
	(void)world;
	player->orientation = (player->orientation + 1) % 4;
	send_to_all_moniteur(srv, moniteur_ppo(player));
	return (ft_strdup("OK\n"));
}

char	*turn_left(t_srv *srv, t_world_state *world, t_client *player)
{
	(void)world;
	player->orientation -= 1;
	if ((int)player->orientation < 0)
		player->orientation = 3;
	if ((int)player->orientation > 3)
		player->orientation = 0;
	send_to_all_moniteur(srv, moniteur_ppo(player));
	return (ft_strdup("OK\n"));
}
