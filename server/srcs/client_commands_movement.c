/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_movement.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:42:39 by selver            #+#    #+#             */
/*   Updated: 2022/01/09 15:31:01 by jayache          ###   ########.fr       */
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

char	*kick(t_srv *srv, t_world_state *world, t_client *client)
{
	t_vector2	direction;
	t_list		*current;
	t_client	*target;
	int			dir;
	char		*format;

	if (client->orientation == NORTH)
	{
		direction = ft_vector2(0, 1);
		dir = 7;
	}
	else if (client->orientation == EAST)
	{
		direction = ft_vector2(1, 0);
		dir = 5;
	}
	else if (client->orientation == SOUTH)
	{
		direction = ft_vector2(0, -1);
		dir = 3;
	}
	else if (client->orientation == WEST)
	{
		direction = ft_vector2(-1, 0);
		dir = 1;
	}
	if (asprintf(&format, "deplacement %d\n", dir) < 0)
		ft_error("Fatal: asprintf a retourné une erreur (" __FILE__ " !!\n");
	current = world->client_list;
	send_to_all_moniteur(srv, moniteur_pex(client));
	while (current)
	{
		target = current->content;
		if (target->p_x == client->p_x + direction.x
				&& target->p_y == client->p_y + direction.y)
		{
			simple_send(srv, target->id, format);
			send_to_all_moniteur(srv, moniteur_ppo(target));
		}
		current = current->next;
	}
	free(format);
	return (ft_strdup("OK\n"));
}
