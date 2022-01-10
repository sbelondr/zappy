/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:20:26 by selver            #+#    #+#             */
/*   Updated: 2022/01/10 11:54:26 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "struct.h"

int				asprintf(char **strp, const char *fmt, ...);

t_param			parse_input(int ac, char **av);
t_world_state	init_world(t_param param);
t_client		*new_client(int id);
int				*get_case(t_world_state *world, int x, int y);
int				quantity_of_elements(int *square);

/*
 * GAMEPLAY
 */

char			*action_see_string(t_srv *srv, t_world_state *wld, t_client *c);
char			*avance(t_srv *srv, t_world_state *wld, t_client *c);
char			*turn_right(t_srv *srv, t_world_state *wld, t_client *c);
char			*turn_left(t_srv *srv, t_world_state *wld, t_client *c);
char			*see_inventaire(t_srv *srv, t_world_state *wld, t_client *c);
char			*pickup_item(t_srv *srv, t_world_state *wld, t_client *c);
char			*putdown_item(t_srv *srv, t_world_state *wld, t_client *c);
char			*player_fork(t_srv *srv, t_world_state *wld, t_client *c);
char			*broadcast(t_srv *srv, t_world_state *wld, t_client *c);
char			*ritual(t_srv *srv, t_world_state *wld, t_client *c);
char			*kick(t_srv *srv, t_world_state *world, t_client *client);

/*
 * HELPERS
 */

void			append_command(t_client *client, t_command to_append);
void			shift_command(t_client *client);
t_command		new_command(t_command_type command, char *arg, int cooldown);
t_game_action	get_action_from_enum(t_command_type command);
void			simple_send(t_srv *srv, int id, char *msg);
int				add_to_team(t_srv *srv, char *team_name, int id);
t_client		*get_current_client(t_srv *srv, int i);
t_egg			*get_egg_by_id(t_world_state *world, int id);
t_client		*get_client_by_id(t_srv *srv, int id);
struct timeval	delta_to_time(int delta);
int				add_egg_to_team(t_world_state *wld, char *team_name, int egg_id);

/*
 * GAME
 */

void			game_tick(t_srv *srv);

/*
 * MONITEUR
 */

char			*moniteur_msz(t_world_state *world);
char			*moniteur_bct(t_world_state *world, int x, int y);
char			*moniteur_mct(t_world_state *world);
char			*moniteur_sgt(t_world_state *world);
char			*moniteur_tna(t_world_state *world);
char			*moniteur_pnw(t_client *client);
char			*moniteur_ppo(t_client *client);
char			*moniteur_pgt(t_client *client, int ressource);
char			*moniteur_pdr(t_client *client, int ressource);
char			*moniteur_enw(t_egg *egg);
char			*moniteur_pin(t_client *client);
char			*moniteur_pex(t_client *client);
char			*moniteur_pbc(int id, char *msg);
char			*moniteur_pic(t_world_state *wld, t_client *client);
char			*moniteur_pie(int x, int y, int success);
void			send_to_all_moniteur(t_srv *srv, char *msg);

#endif
