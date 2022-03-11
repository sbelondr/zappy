/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 11:20:26 by selver            #+#    #+#             */
/*   Updated: 2022/03/11 11:00:48 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "struct.h"

int				asprintf(char **strp, const char *fmt, ...);

/*
 * SETUP
 */

void			setup_signal(void);
void			ft_quit(int sig);
void			ft_add_new_client(t_srv *srv, fd_set *readfds);
int				ft_set_max_sd(t_srv *srv, fd_set *readfds);
t_srv			*init_srv(t_param *param, t_world_state *st);

t_param			parse_input(int ac, char **av);
t_world_state	init_world(t_param param);
t_client		*new_client(int id);
int				*get_case(t_world_state *world, int x, int y);
int				quantity_of_elements(int *square);

/*
 * GAME LOOP
 */

void			game_tick(t_srv *srv);
void			command_lexer(t_srv *srv, char *buf, int i);
struct timeval	delta_to_time(int delta);

/*
 * GAME LOGIC
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
 * EGGS
 */

t_egg			*new_egg(t_world_state *world, char const *team_name, t_vector2 pos, int parent_id);
t_egg			*get_egg_by_id(t_world_state *world, int id);
void			rotten_egg(t_srv *srv, t_egg *egg);

/*
 * Clients
 */

t_client		*get_client_by_id(t_srv *srv, int id);
void			kill_player(t_srv *srv, t_client *player);
int				same_position(t_client *a, t_client *b);
int				is_special_team_member(t_client *client);

/*
 * Commands
 */

void			append_command(t_client *client, t_command to_append);
void			shift_command(t_client *client);
void			clear_commands(t_client *client);
t_command		new_command(t_command_type command, char *arg, int cooldown);

/*
 * TEAMS
 */

int				add_to_team(t_srv *srv, char *team_name, int id);
int				add_egg_to_team(t_world_state *wld, char *team_name, int egg_id);
int				available_slots(t_srv *srv, t_team *team);
t_team			*get_team_by_name(t_world_state *world, char *team_name);

/*
 * HELPERS
 */

t_vector2		rotate_vector(t_vector2 vec, int direction);
int				is_valid_item(char const *item);
int				can_print(t_param *param, t_logtype log_level);
t_game_action	get_action_from_enum(t_command_type command);
const char	*ressource_name(int ressource_id, int localized);

/*
 * CLIENT COMMUNICATION
 */

void			parse_command_set(t_srv *srv, t_client *tester, char *command);
void			ft_client_exit(t_srv *srv, int id);
void			ft_client_exit(t_srv *srv, int i);
void			ft_client_sent_data(t_srv *srv, char *buff, int valread, int i);
void			ft_listen_srv(t_srv *srv, fd_set *readfds);
void			simple_send(t_srv *srv, int id, char *msg);
void			simple_send_no_free(t_srv *srv, int id, char const *msg);

/*
 * RESSOURCE GENERATION
 */

void			generate_ressource_standard(t_world_state world);
void			generate_ressource_uniform(t_world_state world);

/*
 * MONITEUR COMMANDS
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
char			*moniteur_mac(t_world_state *world);
char			*moniteur_tac(t_world_state *world);
char			*moniteur_pex(t_client *client);
char			*moniteur_pdi(t_client *client);
char			*moniteur_plv(t_client *client);
char			*moniteur_pbc(int id, char *msg);
char			*moniteur_pic(t_world_state *wld, t_client *client);
char			*moniteur_edi(t_egg *egg);
char			*moniteur_pie(int x, int y, int success);
char			*moniteur_eht(t_egg *egg);
void			send_to_all_moniteur(t_srv *srv, char *msg);

/*
 * COLORS
 */

void			red(void);
void			cyan(void);
void			purple(void);
void			blue(void);
void			yellow(void);
void			green(void);
void			reset(void);
void			set_color(t_colors color, int param);

/*
 * ERROR HANDLING
 */

void			emergency_exit(char const *perror_prefix);

#endif
