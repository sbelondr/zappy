/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:20:26 by selver            #+#    #+#             */
/*   Updated: 2021/07/17 14:36:20 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

#include "struct.h"

t_param			parse_input(int ac, char **av);
t_world_state	init_world(t_param param);
t_client		*new_client(void);
int				*get_case(t_world_state *world, int x, int y);
int				quantity_of_elements(t_world_state *world, int *square);

#endif

/*
 * GAMEPLAY
 */

char			*action_see_string(t_world_state *world, t_client *client);
char			*avance(t_world_state *world, t_client *client);
char			*turn_right(t_world_state *world, t_client *client);
char			*turn_left(t_world_state *world, t_client *client);
char			*see_inventaire(t_world_state *world, t_client *client);
char			*pickup_item(t_world_state *world, t_client *client);
char			*putdown_item(t_world_state *world, t_client *client);
