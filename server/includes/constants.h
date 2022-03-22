/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 08:11:31 by selver            #+#    #+#             */
/*   Updated: 2022/03/22 10:10:27 by jayache          ###   ########.fr       */
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
#define FLAG_NORESGEN		32

#define STANDARDFOOD		"nourriture"
#define STANDARDLINEMATE	"linemate"
#define STANDARDDERAUMERE	"deraumere"
#define STANDARDSIBUR		"sibur"
#define STANDARDMENDIANE	"mendiane"
#define STANDARDPHIRAS		"phiras"
#define STANDARDTHYSTAME	"thystame"
#define STANDARDPLAYER		"player"

#define STANDARD_COMMAND_VOIR			"voir"
#define STANDARD_COMMAND_GAUCHE			"gauche"
#define STANDARD_COMMAND_DROITE			"droite"
#define STANDARD_COMMAND_AVANCE			"avance"
#define STANDARD_COMMAND_KICK			"kick"
#define STANDARD_COMMAND_INCANTATION	"incantation"
#define STANDARD_COMMAND_INVENTAIRE		"inventaire"
#define STANDARD_COMMAND_BROADCAST		"broadcast"
#define STANDARD_COMMAND_POSE			"pose"
#define STANDARD_COMMAND_PRENDRE		"prendre"
#define STANDARD_COMMAND_FORK			"fork"

#define STANDARD_FORK_ANSWER			"niveau actuel : %d\n"
#define STANDARD_FORK_ANSWER_CURRENT	"elevation en cours\n"
#define STANDARD_KICK_ANSWER			"deplacement %d\n"

#define EXIT_BAD_PARAMETER				2

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
	PLAYER
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
