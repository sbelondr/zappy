/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:08:55 by selver            #+#    #+#             */
/*   Updated: 2021/03/04 15:37:57 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdint.h"

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
