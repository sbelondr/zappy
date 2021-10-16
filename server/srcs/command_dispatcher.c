/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 10:20:43 by selver            #+#    #+#             */
/*   Updated: 2021/10/16 10:48:53 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "functions.h"

t_game_action	get_action_from_enum(t_command_type command)
{
	t_game_action array[15];

	bzero(array, sizeof(t_game_action) * 15);
	array[1] = avance;
	array[2] = turn_right;
	array[3] = turn_left;
	array[4] = action_see_string;
	array[5] = see_inventaire;
	array[6] = pickup_item;
	array[7] = putdown_item;
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
