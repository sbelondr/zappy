/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 08:11:31 by selver            #+#    #+#             */
/*   Updated: 2022/03/06 10:05:58 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

#define BUFF_READ			2024

#define ERROR_SEND_CLIENT	"Le client %d n'a pas reçu le message. Je vais lui monter ses morts \n"
#define ERROR_CLIENT_EXIT	"Le client %d s'est barré sans payer\n"

#define MAX_HUNGER			126;

#define GRAPHIC_TEAM		"GRAPHIC"
#define TESTER_TEAM			"TESTER"

#define USAGE	"Usage: ./serveur -p <port> -x <width> -y <height> -n <team> [<team>] [<team>] ... -c <nb> -t <t>\n" \
	"-p, --port <port>          numero de port\n" \
	"-x, --width <n>            largeur du Monden\n"\
	"-y, --height <n>           hauteur du Monde\n"\
	"-n, --name <name>          nom_equipe_1 nom_equipe_2 ...\n"\
	"-c, --clients-allowed <n>  nombre de client autorises au commencement du jeu\n" \
	"-t, --time <n>             diviseur de l'unite de temps (plus t est grand, plus le jeu va vite)\n"\
	"-m, --max <n>              nombre maximum de clients par equipe (300 par defaut)\n" \
	"-h, --help                 affiche l'usage\n" \
	"-H, --hunger               desactive la faim\n" \
	"-v, --verification         permet la connexion du groupe special TESTER, pour passer les tests unitaires\n" \
	"-G, --gen-frequency <N>    regenere des ressources tous les N ticks (1000 par defaut)\n" \
	"-g, --gen-function <F>     change l'algorithme de generation de ressources. Valeurs possibles : STANDARD, UNIFORM\n" \
	"-s, --silent               n'imprime rien.\n" \
	"-V, --verbose              imprime TOUT.\n" \
	"    --[no-]print-ticks     imprime le numero de tick quand un nouveau tour commence.\n" \
	"    --[no-]print-sent      imprive ce que le serveur renvoie au client.\n" \
	"    --[no-]print-received  imprime ce que le serveur recoit des clients.\n" \
	"    --[no-]print-info      imprime des infos supplementaires.\n" \
	"    --[no-]print-action    imprime les actions que les entreprennent.\n" \
	"    --[no-]print-connexion imprime les nouvelles connexions.\n" \
	"    --[no-]print-egg-death imprime les oeufs qui pourrissent.\n" \
	"    --[no-]print-death     imprime les morts des joueurs.\n" \
	"    --[no-]print-error     imprime les erreurs du serveur.\n" \
	"-C, --[no-]print-colors    colorize les messages selon leur type.\n" \


#define FLAG_TESTER			1
#define FLAG_NOHUNGER		2
#define FLAG_TICK			4
#define FLAG_SILENT			8
#define FLAG_COLOR			16

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
	LAMENDIANE,
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
