/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_ritual.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 09:43:16 by jayache           #+#    #+#             */
/*   Updated: 2022/03/10 10:41:40 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

/*
 * RETURNS A int[8] CONTAINING COST OF RITUAL
 * LAST INT IS THE NUMBER OF PLAYERS
 * RETURN DATA IS STATIC SO THE POINTER STAYS VALID AFTER RETURN
 */

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
			return (0);
	}
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
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
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
