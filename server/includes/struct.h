/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:08:55 by selver            #+#    #+#             */
/*   Updated: 2021/10/16 10:47:52 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "includes.h"
#include "constants.h"

/*
** Commandes du client
*/

typedef struct	s_command
{
	t_command_type	command;
	char			*arg;
	char			cooldown;
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
	int				id;
	t_orientation	orientation;
	int				ressource[7];
}				t_client;

/*
** Donnees en input
*/

typedef struct	s_team
{
	char				*team_name;	
	t_list				*team_clients;
}				t_team;

typedef struct	s_param
{
	uint8_t		flags;
	int			port;
	int			world_width;
	int			world_height;
	int			time_delta;
	int			allowed_clients_amount;
	t_list		*team_list;	
}				t_param;

typedef struct	s_world_state
{
	int			***map; //Note: c'est un pointer vers pointers vers tableau de 7 cases
	t_param		params;
	t_list		*client_list;
}				t_world_state;

typedef struct	s_srv
{
	int						master_sck;
	struct sockaddr_in		address;
	int						addrlen;
	int						*client_sck;
	t_param					*param;
	t_world_state			*world;
}				t_srv;

typedef char* (*t_game_action)(t_world_state*, t_client*);

#endif
