/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:08:55 by selver            #+#    #+#             */
/*   Updated: 2021/03/06 09:15:32 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdint.h"

typedef enum	e_command_type
{
	AVANCE,
	DROITE,
	GAUCHE,
	VOIR

}				t_command_type;

typedef struct	s_command
{
	t_command_type command;
	
}				t_command;
typedef struct	s_client
{
	
}				t_client;

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
