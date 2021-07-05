/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 08:11:31 by selver            #+#    #+#             */
/*   Updated: 2021/07/05 10:39:16 by selver           ###   ########.fr       */
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
	AVANCE,
	DROITE,
	GAUCHE,
	VOIR,
	INVENTAIRE,
	PRENDRE,
	POSER,
	EXPULSER,
	BROADCAST,
	INCANTATION,
	FORK,
	CONNECT_NBR
}				t_command_type;


typedef enum	e_orientation
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}				t_orientation;

typedef struct	s_command
{
	t_command_type	command;
	char			*arg;
}				t_command;

#endif
