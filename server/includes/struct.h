/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:08:55 by selver            #+#    #+#             */
/*   Updated: 2022/02/20 10:50:43 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "includes.h"
# include "constants.h"

/*
 ** Commandes du client
 */

typedef struct	s_command
{
	t_command_type	command;
	char			*arg;
	short			cooldown;
}				t_command;

/*
 ** Bookkeeping (Les clients ne peuvent envoyer que dix requetes sans recevoir de reponse)
 */

typedef struct	s_client
{
	t_command		buffer[10];
	char			lvl;
	char			in_incantation;
	int				life;
	int				p_x;
	int				p_y;
	int				id;
	int				hunger;
	t_orientation	orientation;
	int				ressource[7];
	char			*team_name;
}				t_client;

typedef struct	s_egg
{
	char		*team_name;
	int			p_x;
	int			p_y;
	int			maturity;
	int			food;
	int			hunger;
	int			used;
	int			id;
	int			father_id;
}				t_egg;

/*
 ** Donnees en input
 */

typedef struct	s_team
{
	char		*team_name;	
	t_list		*team_clients;
	t_list		*team_eggs;
}				t_team;

typedef struct	s_param
{
	uint8_t		flags;
	int			port;
	int			world_width;
	int			world_height;
	int			time_delta;
	int			allowed_clients_amount;
	int			team_hard_limit;
	int			generation_frequency;
	t_generate	generate_function;
	t_list		*team_list;	
}				t_param;

typedef struct	s_world_state
{
	int			***map; //Note: c'est un pointer vers pointers vers tableau de 7 cases
	t_param		params;
	t_list		*client_list;
	t_list		*egg_list;
}				t_world_state;

typedef struct	s_srv
{
	int						master_sck;
	struct sockaddr_in		address;
	int						addrlen;
	int						*client_sck;
	t_param					*param;
	t_world_state			*world;
	uint64_t				frame_nbr;
}				t_srv;

typedef char*	(*t_game_action)(t_srv*, t_world_state*, t_client*);

#endif
