/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   localized_strings_fr.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 09:22:38 by jayache           #+#    #+#             */
/*   Updated: 2022/03/11 12:05:42 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCALIZED_STRINGS
# define LOCALIZED_STRINGS

#define USAGE	"Usage: ./serveur -p <port> -x <width> -y <height> -n <team> [<team>] [<team>] ... -c <nb> -t <t>\n" \
	"Les arguments obligatoires aux options longues le sont aussi pour les options courtes.\n" \
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
	"-l, --log-replay [NAME]    sauvegarde la partie sous le nom donne en parametre.\n" \
	"-P, --pedantic				fait tourner le serveur en mode strictement conformant au sujet, sans extensions.\n" \
	"-L, --localized			localize les commandes. Aucun effet en français.\n"

#define LOCUPPERCASEFOOD		"NOURRITURE"
#define LOCUPPERCASELINEMATE	"LINEMATE"
#define LOCUPPERCASEDERAUMERE	"DERAUMERE"
#define LOCUPPERCASESIBUR		"SIBUR"
#define LOCUPPERCASEMENDIANE	"MENDIANE"
#define LOCUPPERCASEPHIRAS		"PHIRAS"
#define LOCUPPERCASETHYSTAME	"THYSTAME"
#define LOCUPPERCASEPLAYER		"PLAYER"

#define LOCFOOD			"nourriture"
#define LOCLINEMATE		"linemate"
#define LOCDERAUMERE	"deraumere"
#define LOCSIBUR		"sibur"
#define LOCMENDIANE		"mendiane"
#define LOCPHIRAS		"phiras"
#define LOCTHYSTAME		"thystame"
#define LOCPLAYER		"player"

#define LOC_COMMAND_VOIR	"voir"
#define LOC_COMMAND_GAUCHE	"gauche"
#define LOC_COMMAND_DROITE	"droite"
#define LOC_COMMAND_AVANCE	"avance"
#define LOC_COMMAND_KICK	"kick"
#define LOC_COMMAND_INCANTATION	"incantation"
#define LOC_COMMAND_INVENTAIRE	"inventaire"
#define LOC_COMMAND_BROADCAST	"broadcast"
#define LOC_COMMAND_POSE	"pose"
#define LOC_COMMAND_PRENDRE	"prendre"
#define LOC_COMMAND_FORK	"fork"

#define LOC_FORK_ANSWER				"niveau actuel : %d\n"
#define LOC_FORK_ANSWER_CURRENT		"elevation en cours\n"
#define LOC_KICK_ANSWER				"deplacement %d\n"

#define ERROR_SEND_CLIENT		"Le client #%d n'a pas reçu le message. Je vais lui monter ses morts \n"
#define ERROR_CLIENT_EXIT		"Le client #%d s'est barré sans payer\n"
#define ERROR_NO_EGG			"ERREUR FATALE: Impossible de trouver un oeuf valide pour le client.!\n"

#define ERROR_INV_PARAM_NAN			"Paramètre invalide: '%s' n'est pas un nombre.\n"
#define ERROR_INV_PARAM_TOO_SMALL	"Paramètre invalide: %ld est trop petit. La valeur minimale acceptée pour ce paramètre est %d\n"
#define ERROR_INV_PARAM_TOO_BIG		"Paramètre invalide: %ld est trop grand. La valeur maximale acceptée pour ce paramètre est %d\n"
#define ERROR_INV_PARAM_FILE		"Paramètre invalide: Ne peut pas ouvrir %s: "
#define ERROR_INV_PARAM_GEN			"Paramètre invalide: %s n'est pas une fonction reconnue.\n"

#define ERROR_INV_OPT_TOO_MANY_REPLAYS	"Option invalide: Ne peut générer qu'un seul replay à la fois. Utilisez cp pour le copier !\n"
#define ERROR_INV_OPT_UNKNOWN			"Option inconnue: %s\n" 
#define ERROR_INV_OPT_END				"Erreur: %s prend un argument.\n"

#define ERROR_MISSING_PARAM_PORT	"Paramètre manquant: Numéro de port (-p)\n"
#define ERROR_MISSING_PARAM_WIDTH	"Paramètre manquant: Largeur du monde (-x)\n"
#define ERROR_MISSING_PARAM_HEIGHT	"Paramètre manquant: Hauteur du monde (-y)\n"
#define ERROR_MISSING_PARAM_DELTA	"Paramètre manquant: Vitesse du monde (-d)\n"
#define ERROR_MISSING_PARAM_ACA		"Paramètre manquant: Clients autorisés par équipes sans oeufs (-c)\n"
#define ERROR_MISSING_PARAM_TEAM	"Paramètre manquant: Nom d'équipe (Min. 1)(-n)\n"


#define LOG_CLIENTS_LEFT		"Il reste encore %ld clients sur le serveur !\n"
#define LOG_INCOMPLETE_COMMAND	"%ld: ERREUR! La commande envoyée par #%d [%d] n'est pas complète." \
	"Était-elle trop longue? Commande reçue: %s"
#define LOG_UNDEAD_CLIENT		"Le client #%d est mort, mais il envoie toujours des requêtes !\n"
#define LOG_CONNEXION_EGG		"Nouveau client connecté avec l'oeuf #%d\n"
#define LOG_CONNEXION_POSITION	"Nouveau joueur a la position x: %d y: %d\n"
#define LOG_REFUSED_CONNEXION	"%ld: Connexion refusée pour #%d [%d]\n"
#define LOG_EGG_READY_TO_HATCH	"%ld: Un oeuf est prêt à éclore!\n"

#endif
