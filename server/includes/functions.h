/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:20:26 by selver            #+#    #+#             */
/*   Updated: 2022/02/22 14:20:12 by jayache          ###   ########.fr       */
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
char			*connect_nbr(t_srv *srv, t_world_state *world, t_client *player);

/*
 * HELPERS
 */

char			**split_args(char *str, int expected);
int				is_special_team_member(t_client *client);
void			append_command(t_client *client, t_command to_append);
void			shift_command(t_client *client);
void			clear_commands(t_client *client);
t_command		new_command(t_command_type command, char *arg, int cooldown);
t_game_action	get_action_from_enum(t_command_type command);
void			simple_send(t_srv *srv, int id, char *msg);
int				add_to_team(t_srv *srv, char *team_name, int id);
t_client		*get_current_client(t_srv *srv, int i);
t_egg			*get_egg_by_id(t_world_state *world, int id);
t_client		*get_client_by_id(t_srv *srv, int id);
struct timeval	delta_to_time(int delta);
int				add_egg_to_team(t_world_state *wld, char *team_name, int egg_id);
t_team			*get_team_by_name(t_world_state *world, char *team_name);
void			rotten_egg(t_srv *srv, t_egg *egg);
int				available_slots(t_srv *srv, t_team *team);
void			kill_player(t_srv *srv, t_client *player);
int				same_position(t_client *a, t_client *b);
/*
 * GAME
 */

void			game_tick(t_srv *srv);
void			ft_lexer(t_srv *srv, char *buf, int i);

/*
 * CLIENT COMMUNICATION
 */

void			parse_command_set(t_srv *srv, t_client *tester, char *command);
void			ft_client_exit(t_srv *srv, int id);

/*
 * RESSOURCE GENERATION
 */

void			generate_ressource_standard(t_world_state world);
void			generate_ressource_uniform(t_world_state world);

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
char			*moniteur_ebo(t_egg *egg);
char			*moniteur_pin(t_client *client);
char			*moniteur_pfk(t_client *client);
char			*moniteur_pex(t_client *client);
char			*moniteur_pdi(t_client *client);
char			*moniteur_plv(t_client *client);
char			*moniteur_pbc(int id, char *msg);
char			*moniteur_pic(t_world_state *wld, t_client *client);
char			*moniteur_edi(t_egg *egg);
char			*moniteur_pie(int x, int y, int success);
char			*moniteur_eht(t_egg *egg);
void			send_to_all_moniteur(t_srv *srv, char *msg);

#endif
