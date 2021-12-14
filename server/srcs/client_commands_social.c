/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_social.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:15:43 by selver            #+#    #+#             */
/*   Updated: 2021/12/14 10:59:56 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char	*player_fork(t_srv *srv, t_world_state *world, t_client *player)
{
	t_egg	egg;
	t_list	*current;
	int		maxid;

	maxid = 0;
	egg.team_name = ft_strdup(player->team_name);
	egg.p_x = player->p_x;
	egg.p_y = player->p_y;
	egg.maturity = 600;
	egg.father_id = player->id;
	egg.maturity = 600;
	current = world->egg_list;
	while (current)
	{
		if (((t_egg *)current->content)->id > maxid)
			maxid = ((t_egg *)current->content)->id;
		current = current->next;
	}
	egg.id = maxid + 1;
	ft_lst_append(&world->egg_list, ft_lstnew(&egg, sizeof(t_egg)));
	add_egg_to_team(world, player->team_name, egg.id);
	printf("[%d] a pondu un oeuf avec l'ID %d !", player->id, egg.id);
	send_to_all_moniteur(srv, moniteur_enw(&egg));
	return (ft_strdup("OK\n"));
}

/*
 * Donne la direction du broadcast pour une paire de joueur donnée
 * PARAMS:	t_world_state *world -> world state	
 *			t_client *emitter -> The client who's speaking
 *			t_client *recepter -> The client that's listening
 * RETURNS:	int	-> The num of the case giving the direction of the ray
 * TODO: Does not take into account the recepter orientation
 */
static int	b_dir(t_world_state *world, t_client *emitter, t_client *recepter)
{
	int			diff_x;
	int			diff_y;
	int			direction;

	diff_x = emitter->p_x - recepter->p_x;
	diff_y = emitter->p_y - recepter->p_y;
	if (abs(diff_x) > world->params.world_width / 2)
		diff_x *= -1;
	if (abs(diff_y) > world->params.world_height / 2)
		diff_y *= -1;
	diff_y = emitter->p_y - recepter->p_y;
	direction = 0;
	if (diff_x == 0 && diff_y == 0 && emitter->id != recepter->id)
	{
		direction = 0;
	}
	else if (diff_x == 0 && diff_y < 0)
		direction = 1;
	else if (diff_x == 0 && diff_y > 0)
		direction = 2;
	else if (diff_x < 0 && diff_y == 0)
		direction = 3;
	else if (diff_x > 0 && diff_y == 0)
		direction = 4;
	else if (diff_x > 0 && diff_y > 0)
		direction = 5;
	else if (diff_x < 0 && diff_y < 0)
		direction = 6;
	else if (diff_x < 0 && diff_y < 0)
		direction = 7;
	else if (diff_x < 0 && diff_y > 0)
		direction = 8;
	return (direction);
}

char	*broadcast(t_srv *srv, t_world_state *world, t_client *player)
{
	char	*arg;
	char	*msg;
	int		error;
	t_list	*current;
	t_client	*c;

	arg = player->buffer[0].arg;
	current = world->client_list;
	while (current)
	{
		c = current->content;
		error = asprintf(&msg, "%d %s\n", b_dir(world, player, c), arg);
		if (error < 0)
			ft_error("Fatal: asprintf a retourné une erreur (" __FILE__ " !!\n");
		if (!ft_strcmp(c->team_name, "GRAPHIC"))
			simple_send(srv, c->id, moniteur_pbc(player->id, arg));
		else if (c->id != player->id)
			simple_send(srv, c->id, msg);
		current = current->next;
	}
	return (ft_strdup("OK\n"));
}
