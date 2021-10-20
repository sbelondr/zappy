/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:20:26 by selver            #+#    #+#             */
/*   Updated: 2021/10/18 12:28:18 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

#include "struct.h"

t_param			parse_input(int ac, char **av);
t_world_state	init_world(t_param param);
t_client		*new_client(int id);
int				*get_case(t_world_state *world, int x, int y);
int				quantity_of_elements(int *square);


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

/*
 * HELPERS
 */

void			append_command(t_client *client, t_command to_append);
void			shift_command(t_client *client);
t_command		new_command(t_command_type command, char *arg, int cooldown);
t_game_action	get_action_from_enum(t_command_type command);

/*
 * GAME
 */

void			game_tick(t_srv *srv);
#endif
