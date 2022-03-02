/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_social.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:15:43 by selver            #+#    #+#             */
/*   Updated: 2022/03/01 09:22:37 by jayache          ###   ########.fr       */
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
	egg->hunger = 0;
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
	if (can_print(srv->param, LOG_ACTION))
	{
		printf("[%d] a pondu un oeuf avec l'ID %d !", player->id, egg->id);
	}
	send_to_all_moniteur(srv, moniteur_enw(egg));
	return (ft_strdup("ok\n"));
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

static	int	*get_ritual_data(int level)
{
	int	values[8][8] = { 
		{0, 1, 0, 0, 0, 0, 0, 1},
		{0, 1, 1, 1, 0, 0, 0, 2},
		{0, 2, 0, 1, 0, 0, 0, 2},
		{0, 1, 1, 2, 0, 0, 0, 4},
		{0, 1, 2, 1, 3, 0, 0, 4},
		{0, 1, 2, 3, 0, 1, 0, 6},
		{0, 2, 2, 2, 2, 2, 1, 6}
	};
	static int	ret[8];
	memcpy(ret, values[level - 1], 8 * sizeof(int));
	return (ret);
}

static int	is_enough_for_ritual(int level, int players, int *objs)
{
	int	*required;

	required = get_ritual_data(level);
	for (int i = 0; i < 7; ++i)
	{
		if (objs[i] < required[i])
		{
			printf("Not enough %d! %d < %d\n", i, objs[i], required[i]);
			return (0);
		}
	}
	printf("Players: %d / %d\n", players, required[7]);
	return (required[7] <= players);
}

static void	substract_from_ritual(int level, int *objs)
{
	int	*cost;

	cost = get_ritual_data(level);
	for (int i = 0; i < 7; ++i)
		objs[i] -= cost[i];
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
		if (same_position(c, player) && c->lvl == player->lvl && !is_special_team_member(c))
			players++;
		current = current->next;
	}
	printf("Figuring it out for %d %d...\n", player->p_x, player->p_y);
	if (is_enough_for_ritual(player->lvl, players, get_case(world, player->p_x, player->p_y)))
	{
		substract_from_ritual(player->lvl, get_case(world, player->p_x, player->p_y));
		current = world->client_list;
		while (current)
		{
			c = current->content;
			if (same_position(player, c) && c->lvl == player->lvl && c->id != player->id && !is_special_team_member(c))
				c->lvl += 1;
			current = current->next;
		}
		player->lvl += 1;
		success = 1;
	}
	send_to_all_moniteur(srv, moniteur_pie(player->p_x, player->p_y, success));
	error = asprintf(&msg, "niveau actuel : %d\n", player->lvl);
	if (error < 0)
		ft_error("Fatal: asprintf a retourné une erreur (" __FILE__ " !!\n");
	current = world->client_list;
	while (current)
	{
		c = current->content;
		if (same_position(player, c) && c->lvl == player->lvl && !is_special_team_member(c))
		{
			if (c->id != player->id)
				simple_send(srv, c->id, ft_strdup(msg));
			send_to_all_moniteur(srv, moniteur_plv(c));
		}
		current = current->next;
	}
	send_to_all_moniteur(srv, moniteur_bct(srv->world, player->p_x, player->p_y));
	return (msg);
}
