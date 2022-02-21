/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_social.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:15:43 by selver            #+#    #+#             */
/*   Updated: 2022/02/21 09:55:22 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

//TODO: change ft_itoa -- slowest function ever
char	*connect_nbr(t_srv *srv, t_world_state *world, t_client *player)
{
	int		slots;
	int		error;
	char	*ret;

	slots = available_slots(srv, get_team_by_name(world, player->team_name));
	error = asprintf(&ret, "%d\n", slots);
	if (error < 0)
		ft_error("Fatal: asprintf a retourné une erreur (" __FILE__ " !!\n");
	return (ret);
}

char	*player_fork(t_srv *srv, t_world_state *world, t_client *player)
{
	t_egg	*egg;
	t_list	*current;
	int		maxid;

	maxid = -1;
	egg = (t_egg*)malloc(sizeof(t_egg));
	egg->team_name = ft_strdup(player->team_name);
	egg->p_x = player->p_x;
	egg->p_y = player->p_y;
	egg->food = 10;
	egg->maturity = 600;
	egg->father_id = player->id;
	egg->used = 0;
	current = world->egg_list;
	while (current)
	{
		if (((t_egg *)current->content)->id > maxid)
			maxid = ((t_egg *)current->content)->id;
		current = current->next;
	}
	egg->id = maxid + 1;
	ft_lst_append(&world->egg_list, ft_lstnew_no_copy(egg, sizeof(t_egg)));
	add_egg_to_team(world, player->team_name, egg->id);
	printf("[%d] a pondu un oeuf avec l'ID %d !", player->id, egg->id);
	send_to_all_moniteur(srv, moniteur_enw(egg));
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
	direction = 0;
	if (diff_x == 0 && diff_y == 0 && emitter->id != recepter->id)
		direction = 0;
	else if (diff_x == 0 && diff_y < 0)
		direction = 1;
	else if (diff_x == 0 && diff_y > 0)
		direction = 5;
	else if (diff_x < 0 && diff_y == 0)
		direction = 3;
	else if (diff_x > 0 && diff_y == 0)
		direction = 7;
	else if (diff_x > 0 && diff_y > 0)
		direction = 6;
	else if (diff_x < 0 && diff_y < 0)
		direction = 2;
	else if (diff_x > 0 && diff_y < 0)
		direction = 8;
	else if (diff_x < 0 && diff_y > 0)
		direction = 4;
	if (recepter->orientation == EAST && direction != 0)
	{
		direction = (direction + 2);
		if (direction > 8)
			direction %= 8;
	}
	else if (recepter->orientation == SOUTH && direction != 0)
	{
		direction = (direction + 4);
		if (direction > 8)
			direction %= 8;
	}
	else if (recepter->orientation == WEST && direction != 0)
	{
		direction = (direction + 6);
		if (direction > 8)
			direction %= 8;
	}
	return (direction % 9);
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
		if (c->team_name)
		{
			error = asprintf(&msg, "message %d, %s\n", b_dir(world, player, c), arg);
			if (error < 0)
				ft_error("Fatal: asprintf a retourné une erreur (" __FILE__ " !!\n");
			if (!ft_strcmp(c->team_name, "GRAPHIC"))
				simple_send(srv, c->id, moniteur_pbc(player->id, arg));
			else if (c->id != player->id)
				simple_send(srv, c->id, msg);
		}
		current = current->next;
	}
	return (ft_strdup("OK\n"));
}

static int	is_enough_for_ritual(int level, int players, int *objs)
{
	if (level == 1 && players >= 1 && objs[LINEMATE] >= 1)
		return (1);
	else if (level == 2 && players >= 2 && objs[LINEMATE] >= 1 && objs[DERAUMERE] >= 1 && objs[SIBUR] >= 1)
		return (1);
	else if (level == 3 && players >= 2 && objs[LINEMATE] >= 2 && objs[PHIRAS] >= 2 && objs[SIBUR] >= 1)
		return (1);
	else if (level == 4 && players >= 4 && objs[LINEMATE] >= 1 && objs[DERAUMERE] >= 1 
			&& objs[SIBUR] >= 2 && objs[PHIRAS] >= 1 && objs[SIBUR] >= 1 )
		return (1);
	else if (level == 5 && players >= 4 && objs[LINEMATE] >= 1 && objs[DERAUMERE] >= 2 
			&& objs[SIBUR] >= 1 && objs[LAMENDIANE] >= 3 && objs[SIBUR] >= 1 )
		return (1);
	else if (level == 6 && players >= 6 && objs[LINEMATE] >= 1 && objs[DERAUMERE] >= 2 
			&& objs[SIBUR] >= 3 && objs[PHIRAS] >= 1 && objs[SIBUR] >= 1 )
		return (1);
	else if (level == 7 && players >= 6 && objs[LINEMATE] >= 2 && objs[DERAUMERE] >= 2 
			&& objs[SIBUR] >= 2 && objs[LAMENDIANE] >= 2 && objs[PHIRAS] >= 2 && objs[SIBUR] >= 1 && objs[THYSTAME] >= 1)
		return (1);
	return (0);
}

char	*ritual(t_srv *srv, t_world_state *world, t_client *player)
{
	t_list		*current;
	t_client	*c;
	int			players;
	int			success;
	int			error;
	char		*msg;

	players = 0;
	success = 0;
	current = world->client_list;
	while (current)
	{
		c = current->content;
		printf("%d/%d %d/%d %d/%d %p/%p\n", c->p_x, player->p_x, c->p_y, player->p_y, c->lvl, player->lvl, c, player);
		if (c->p_x == player->p_x && c->p_y == player->p_y && c->lvl == player->lvl)
			players++;
		current = current->next;
	}
	if (is_enough_for_ritual(player->lvl, players, get_case(world, player->p_x, player->p_y)))
	{
		current = world->client_list;
		while (current)
		{
			c = current->content;
			if (c->p_x == player->p_x && c->p_y == player->p_y && c->lvl == player->lvl)
				c->lvl += 1;
			current = current->next;
		}
		success = 1;
	}
	error = asprintf(&msg, "Niveau actuel : %d\n", player->lvl);
	if (error < 0)
		ft_error("Fatal: asprintf a retourné une erreur (" __FILE__ " !!\n");
	send_to_all_moniteur(srv, moniteur_pie(player->p_x, player->p_y, success));
	return (msg);
}
