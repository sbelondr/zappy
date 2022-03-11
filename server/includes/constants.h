/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 08:11:31 by selver            #+#    #+#             */
/*   Updated: 2022/03/11 10:26:52 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

#include "localized_strings_fr.h"

#define BUFF_READ			2024


#define MAX_HUNGER			126;

#define GRAPHIC_TEAM		"GRAPHIC"
#define TESTER_TEAM			"TESTER"

#define FLAG_TESTER			1
#define FLAG_NOHUNGER		2
#define FLAG_LOCALIZED		4
#define FLAG_PEDANTIC		8
#define FLAG_COLOR			16

#define STANDARDFOOD		"nourriture"
#define STANDARDLINEMATE	"linemate"
#define STANDARDDERAUMERE	"deraumere"
#define STANDARDSIBUR		"sibur"
#define STANDARDMENDIANE	"mendiane"
#define STANDARDPHIRAS		"phiras"
#define STANDARDTHYSTAME	"thystame"
#define STANDARDPLAYER		"player"

typedef enum	e_colors {
	RESET = 0,
	BLACK = 30,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	PURPLE,
	CYAN,
	GREY
}				t_colors;

typedef enum	e_ressources {
	FOOD,
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME,
}				t_ressources;

typedef enum	e_logtype {
	LOG_TICK		= 1,
	LOG_RECEIVE		= 2,
	LOG_SEND		= 4,
	LOG_ACTION		= 8,
	LOG_PLAYERDEATH	= 16,
	LOG_EGGDEATH	= 32,
	LOG_CONNEXION	= 64,
	LOG_INFO		= 128,
	LOG_ERROR		= 256
}				t_logtype;

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
	COMMAND_BAD_PARAMETER,
	COMMAND_NBR
}				t_command_type;


typedef enum	e_orientation
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}				t_orientation;

struct	s_world_state;
typedef void	(*t_generate)(struct s_world_state);

#endif
