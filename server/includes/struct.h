/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:08:55 by selver            #+#    #+#             */
/*   Updated: 2021/03/06 10:41:12 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdint.h"

/*
** Commandes du client
*/

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

/*
** Bookkeeping (Les clients ne peuvent envoyer que dix requetes sans recevoir de reponse)
*/

typedef struct	s_client
{
	t_command		buffer[10];
	int				lvl;
	int				life;
	int				p_x;
	int				p_y;
	t_orientation	orientation;
	int				ressource[7];
	struct s_client	*next;
}				t_client;

/*
** Donnees en input
*/

typedef struct	s_team_list
{
	char				*team_name;	
	struct	s_team_list	*next;
}				t_team_list;

typedef struct	s_param
{
	uint8_t		flags;
	int			port;
	int			world_width;
	int			world_height;
	int			time_delta;
	int			allowed_clients_amount;
	t_team_list	*team_list;	
}				t_param;

typedef struct	s_world_state
{
	int			***map; //Note: c'est un pointer vers pointers vers tableau de 7 cases
	t_param		params;
	t_client	*client_list;
}				t_world_state;
