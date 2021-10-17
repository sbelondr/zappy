/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 08:11:31 by selver            #+#    #+#             */
/*   Updated: 2021/10/17 09:52:23 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

#define ERROR_SEND_CLIENT "Le client %d n'a pas reçu le message. Je vais lui monter ses morts \n"
#define ERROR_CLIENT_EXIT "Le client %d s'est barré sans payer\n"


typedef enum	e_ressources {
	LINEMATE,
	DERAUMERE,
	SIBUR,
	LAMENDIANE,
	PHIRAS,
	THYSTAME,
	FOOD
}				t_ressources;

typedef enum	e_command_type
{
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
	COMMAND_CONNECT_NBR,
	COMMAND_UNKNOWN,
	COMMAND_NBR
}				t_command_type;


typedef enum	e_orientation
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}				t_orientation;


#endif
