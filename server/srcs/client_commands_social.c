/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_social.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:15:43 by selver            #+#    #+#             */
/*   Updated: 2022/03/10 10:42:24 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

char	*connect_nbr(t_srv *srv, t_world_state *world, t_client *player)
{
	int		slots;
	int		error;
	char	*ret;

	slots = available_slots(srv, get_team_by_name(world, player->team_name));
	error = asprintf(&ret, "%d\n", slots);
	if (error < 0)
		emergency_exit(__FILE__ ": Fatal: asprintf: ");
	return (ret);
}

char	*player_fork(t_srv *srv, t_world_state *world, t_client *player)
{
	t_egg	*egg;

	egg = new_egg(world, player->team_name, ft_vector2(player->p_x, player->p_y), player->id);
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
				emergency_exit(__FILE__ ": Fatal: asprintf: ");
			if (!ft_strcmp(c->team_name, "GRAPHIC"))
				simple_send(srv, c->id, moniteur_pbc(player->id, arg));
			else if (c->id != player->id)
				simple_send(srv, c->id, msg);
		}
		current = current->next;
	}
	return (ft_strdup("OK\n"));
}
