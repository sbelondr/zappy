/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   localized_strings_en.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 09:22:38 by jayache           #+#    #+#             */
/*   Updated: 2022/06/22 09:25:14 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCALIZED_STRINGS
# define LOCALIZED_STRINGS

#define USAGE	"Usage: ./server -p <port> -x <width> -y <height> -n <team> [<team>] [<team>] ... -c <nb> -t <t>\n" \
	"-p, --port <port>          port number\n" \
	"-x, --width <n>            world width\n"\
	"-y, --height <n>           world height\n"\
	"-n, --name <name>          team_name_1 team_name_2 ...\n"\
	"-c, --clients-allowed <n>  number of allowed clients authorized when game starts\n" \
	"-t, --time <n>             time unit diviser (game goes faster as it gets bigger)\n"\
	"-m, --max <n>              maximum amount of players per team (default: 300)\n" \
	"-h, --help                 show this help\n" \
	"-H, --hunger               disable hunger\n" \
	"-v, --verification         allow the connexion of the special group TESTER (to pass unit tests)\n" \
	"-G, --gen-frequency <N>    generate new ressources each N ticks (default: 1000)\n" \
	"-g, --gen-function <F>     set the ressource generation algorithm. Possible values: STANDARD, UNIFORM\n" \
	"-s, --silent               does not print anything. Can be combined with other log options\n" \
	"-V, --verbose              prints everything. Can be combined with other log options.\n" \
	"    --[no-]print-ticks     prints each tick number when a new turn begins.\n" \
	"    --[no-]print-sent      prints everything the server sends to clients.\n" \
	"    --[no-]print-received  prints everything the server receive from clients.\n" \
	"    --[no-]print-info      prints misc information about the game.\n" \
	"    --[no-]print-action    prints some actions status.\n" \
	"    --[no-]print-connexion prints new connexions.\n" \
	"    --[no-]print-egg-death prints egg death.\n" \
	"    --[no-]print-death     prints player death.\n" \
	"    --[no-]print-error     prints non-fatal errors.\n" \
	"-C, --[no-]print-colors    colorizes output.\n" \
	"-l, --log-replay [NAME]    save replay of the game in NAME.\n" \
	"-P, --pedantic             pedantic mode. Removes every extension in order to strictly follow RFC. Rejects clients that do not respect it.\n" \
	"-L, --localized            localizes command name and output. Overriden by --pedantic.\n"

#define LOCUPPERCASEFOOD		"FOOD"
#define LOCUPPERCASELINEMATE	"LINEMATE"
#define LOCUPPERCASEDERAUMERE	"DERAUMERE"
#define LOCUPPERCASESIBUR		"SIBUR"
#define LOCUPPERCASEMENDIANE	"MENDIANE"
#define LOCUPPERCASEPHIRAS		"PHIRAS"
#define LOCUPPERCASETHYSTAME	"THYSTAME"
#define LOCUPPERCASEPLAYER		"PLAYER"

#define LOCFOOD			"food"
#define LOCLINEMATE		"linemate"
#define LOCDERAUMERE	"deraumere"
#define LOCSIBUR		"sibur"
#define LOCMENDIANE		"mendiane"
#define LOCPHIRAS		"phiras"
#define LOCTHYSTAME		"thystame"
#define LOCPLAYER		"player"

#define LOC_COMMAND_VOIR	"see"
#define LOC_COMMAND_GAUCHE	"left"
#define LOC_COMMAND_DROITE	"right"
#define LOC_COMMAND_AVANCE	"forward"
#define LOC_COMMAND_KICK	"kick"
#define LOC_COMMAND_INCANTATION	"incantation"
#define LOC_COMMAND_INVENTAIRE	"inventory"
#define LOC_COMMAND_BROADCAST	"broadcast"
#define LOC_COMMAND_POSE	"put"
#define LOC_COMMAND_PRENDRE	"take"
#define LOC_COMMAND_FORK	"fork"

#define LOC_FORK_ANSWER				"current level : %d\n"
#define LOC_FORK_ANSWER_CURRENT		"elevation in process\n"
#define LOC_KICK_ANSWER				"moved %d\n"

#define ERROR_SEND_CLIENT		"Client #%d did not receive the data. I am angery\n"
#define ERROR_CLIENT_EXIT		"Client #%d left without saying goodbye. That's bad manner!\n"
#define ERROR_NO_EGG			"FATAL ERROR: could not find an egg to spawn in.\n"

#define ERROR_INV_PARAM_NAN			"Invalid parameter: Not a number: %s\n"
#define ERROR_INV_PARAM_TOO_SMALL	"Invalid parameter: Number too small: %ld when min size is %d\n"
#define ERROR_INV_PARAM_TOO_BIG		"Invalid parameter: Number too big: %ld when max size is %d\n"
#define ERROR_INV_PARAM_FILE		"Invalid parameter: Cannot open %s: "
#define ERROR_INV_PARAM_GEN			"Invalid parameter: %s is not a recognized function.\n"

#define ERROR_INV_OPT_TOO_MANY_REPLAYS	"Invalid option: Can only log to 1 file at a time ! Just copy the file if you want more !!\n"
#define ERROR_INV_OPT_UNKNOWN			"Unknown option: %s\n" 
#define ERROR_INV_OPT_END				"Error: unexpected end of argument: %s\n"

#define ERROR_MISSING_PARAM_PORT	"Missing parameter: Port number (-p)\n"
#define ERROR_MISSING_PARAM_WIDTH	"Missing parameter: World width (-x)\n"
#define ERROR_MISSING_PARAM_HEIGHT	"Missing parameter: World height (-y)\n"
#define ERROR_MISSING_PARAM_DELTA	"Missing parameter: World speed (-d)\n"
#define ERROR_MISSING_PARAM_ACA		"Missing parameter: Amount of clients that can connect without needing eggs (-c)\n"
#define ERROR_MISSING_PARAM_TEAM	"Missing parameter: Team names (Min. 1)(-n)\n"

#define LOG_CLIENTS_LEFT		"There are %ld clients left on the server!\n"
#define LOG_INCOMPLETE_COMMAND	"%ld: ERROR! The command sent by #%d [%d] isn't complete." \
	"Was it too long? Command received: %s"
#define LOG_UNDEAD_CLIENT		"Client #%d is dead, but we are still receiving requests!\n"
#define LOG_CONNEXION_EGG		"Connecting new client with egg #%d\n"
#define LOG_CONNEXION_POSITION	"New player at position x: %d y: %d\n"
#define LOG_REFUSED_CONNEXION	"%ld: Connexion refused for #%d [%d]\n"
#define LOG_EGG_READY_TO_HATCH	"%ld: An egg is ready to hatch!\n"
#define LOG_PLAYER_NEW_POSITION	"Player #%d is at position x:%d y:%d\n"


#endif
