/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 08:11:31 by selver            #+#    #+#             */
/*   Updated: 2022/02/20 10:40:07 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

#define ERROR_SEND_CLIENT	"Le client %d n'a pas reçu le message. Je vais lui monter ses morts \n"
#define ERROR_CLIENT_EXIT	"Le client %d s'est barré sans payer\n"

#define MAX_HUNGER			126;

#define GRAPHIC_TEAM		"GRAPHIC"
#define TESTER_TEAM			"TESTER"

#define USAGE	"Usage: ./serveur -p <port> -x <width> -y <height> -n <team> [<team>] [<team>] ... -c <nb> -t <t>\n" \
	"-p numero de port\n" \
	"-x largeur du Monden\n"\
	"-y hauteur du Monde\n"\
	"-n nom_equipe_1 nom_equipe_2 ...\n"\
	"-c nombre de client autorises au commencement du jeu\n-t diviseur de l'unite de temps (plus t est grand, plus le jeu va vite)\n"\
	"-m nombre maximum de clients par equipe (300 par defaut)\n" \
	"-h affiche l'usage\n"

#define FLAG_TESTER			1
#define FLAG_NOHUNGER		2

typedef enum	e_ressources {
	FOOD,
	LINEMATE,
	DERAUMERE,
	SIBUR,
	LAMENDIANE,
	PHIRAS,
	THYSTAME,
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

struct	s_world_state;
typedef void	(*t_generate)(struct s_world_state);

#endif
