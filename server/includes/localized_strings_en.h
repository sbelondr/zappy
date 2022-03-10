/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   localized_strings_en.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 09:22:38 by jayache           #+#    #+#             */
/*   Updated: 2022/03/10 10:15:19 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCALIZED_STRINGS
# define LOCALIZED_STRINGS

#define USAGE	"Usage: ./serveur -p <port> -x <width> -y <height> -n <team> [<team>] [<team>] ... -c <nb> -t <t>\n" \
	"-p, --port <port>          numero de port\n" \
	"-x, --width <n>            largeur du monde\n"\
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
	"-l, --log-replay [NAME]    sauvegarde la partie sous le nom donne en parametre.\n"

#define LOCFOOD		"NOURRITURE"
#define LOCLINEMATE	"LINEMATE"
#define LOCDERAUMERE "DERAUMERE"
#define LOCSIBUR	"SIBUR"
#define LOCMENDIANE	"MENDIANE"
#define LOCPHIRAS	"PHIRAS"
#define LOCTHYSTAME	"THYSTAME"

#define ERROR_SEND_CLIENT		"Le client #%d n'a pas reçu le message. Je vais lui monter ses morts \n"
#define ERROR_CLIENT_EXIT		"Le client #%d s'est barré sans payer\n"
#define ERROR_NO_EGG			"FATAL ERROR: could not find an egg to spawn in.\n"

#define ERROR_INV_PARAM_NAN			"Invalid parameter: Not a number: %s\n"
#define ERROR_INV_PARAM_TOO_SMALL	"Invalid parameter: Number too small: %ld when min size is %d\n"
#define ERROR_INV_PARAM_TOO_BIG		"Invalid parameter: Number too big: %ld when max size is %d\n"
#define ERROR_INV_PARAM_FILE		"Invalid parameter: Cannot open %s: "

#define ERROR_INV_OPT_TOO_MANY_REPLAYS	"Invalid option: Can only log to 1 file at a time ! Just copy the file if you want more !!\n"
#define ERROR_INV_OPT_UNKNOWN			"Unknown option: %s\n" 
#define ERROR_INV_OPT_END				"Error: unexpected end of argument: %s\n"

#define ERROR_MISSING_PARAM_PORT	"Missing parameter: Port number (-p)\n"
#define ERROR_MISSING_PARAM_WIDTH	"Missing parameter: World width (-x)\n"
#define ERROR_MISSING_PARAM_HEIGHT	"Missing parameter: World height (-y)\n"
#define ERROR_MISSING_PARAM_DELTA	"Missing parameter: World speed (-d)\n"
#define ERROR_MISSING_PARAM_ACA		"Missing parameter: Amount of clients that can connect without needing eggs (-c)\n"
#define ERROR_MISSING_PARAM_TEAM	"Missing parameter: Team names (Min. 1)(-n)\n"

#define LOG_CLIENTS_LEFT		"Il reste encore %ld clients sur le serveur !\n"
#define LOG_INCOMPLETE_COMMAND	"%ld: ERREUR! La commande envoyée par #%d [%d] n'est pas complète." \
	"Était-elle trop longue? Commande reçue: %s"
#define LOG_CONNEXION_EGG		"Connecting new client with egg #%d\n"
#define LOG_CONNEXION_POSITION	"New player at position x: %d y: %d\n"


#endif
