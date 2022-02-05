/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 10:20:43 by selver            #+#    #+#             */
/*   Updated: 2022/02/05 10:40:52 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "functions.h"

static char		*unknown_command(t_srv *srv, t_world_state *world, t_client *client)
{
	(void)world;
	(void)client;
	(void)srv;
	return (ft_strdup("???"));
}

t_game_action	get_action_from_enum(t_command_type command)
{
	t_game_action array[COMMAND_NBR + 1];

	ft_bzero(array, sizeof(t_game_action) * COMMAND_NBR);
	array[COMMAND_UNKNOWN] = unknown_command;
	array[COMMAND_AVANCE] = avance;
	array[COMMAND_DROITE] = turn_right;
	array[COMMAND_GAUCHE] = turn_left;
	array[COMMAND_VOIR] = action_see_string;
	array[COMMAND_INVENTAIRE] = see_inventaire;
	array[COMMAND_PRENDRE] = pickup_item;
	array[COMMAND_POSER] = putdown_item;
	array[COMMAND_FORK] = player_fork;
	array[COMMAND_BROADCAST] = broadcast;
	array[COMMAND_EXPULSER] = kick;
	array[COMMAND_INCANTATION] = ritual;
	array[COMMAND_CONNECT_NBR] = connect_nbr;
	return (array[command]);
}

/*
	COMMAND_NONE,
	COMMAND_AVANCE,
	COMMAND_DROITE,
	COMMAND_GAUCHE,
	COMMAND_VOIR,
	COMMAND_INVENTAIRE,
	COMMAND_PRENDRE,
	COMMAND_POSER,
	COMMAND_EXPULSER,
	COMMAND_BROADCAST,
	COMMAND_INCANTATION,
	COMMAND_FORK,
	COMMAND_CONNECT_NBR
 */
