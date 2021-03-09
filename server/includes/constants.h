/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 08:11:31 by selver            #+#    #+#             */
/*   Updated: 2021/03/09 09:32:26 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

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
	SUD,
	WEST
}				t_orientation;

typedef struct	s_command
{
	t_command_type	command;
	char			*arg;
}				t_command;

#endif
