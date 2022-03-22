/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_tick.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:34:19 by selver            #+#    #+#             */
/*   Updated: 2022/03/22 09:19:27 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static void	treat_command(t_srv *srv, t_client *client, int client_id)
{
	char *msg;

	t_game_action act = get_action_from_enum(client->buffer[0].command);
	msg = act(srv, srv->world, client);
	simple_send(srv, client->id, msg);
	shift_command(client);
}

void	egg_tick(t_srv *srv, t_list *egg_list)
{
	t_egg	*egg;

	while (egg_list)
	{
		egg = egg_list->content;
		egg_list = egg_list->next;
		if (egg->maturity > 0)
		{
			egg->maturity--;
			if (egg->maturity == 0)
			{
				if (can_print(srv->param, LOG_INFO))
				{
					purple();
					printf(LOG_EGG_READY_TO_HATCH, srv->frame_nbr);
					reset();
				}
				send_to_all_moniteur(srv, moniteur_eht(egg));
			}
		}
		else
		{
			if (egg->food == 0 && egg->hunger == 0)
				rotten_egg(srv, egg);
			else if (egg->hunger <= 0)
			{
				egg->food--;
				egg->hunger = MAX_HUNGER;
			}
			else
				egg->hunger--;
		}
	}
}

void	setup_ritual_client(t_srv *srv, t_client *client, t_client *client_bis)
{
	if (client_bis->p_x == client->p_x && client_bis->p_y == client->p_y && client->lvl == client_bis->lvl && !is_special_team_member(client_bis))
	{
		if (client_bis->buffer[0].command != COMMAND_INCANTATION)
			client_bis->in_incantation = 1;
		if (use_localized_string(srv->param))
			simple_send_no_free(srv, client_bis->id, LOC_FORK_ANSWER_CURRENT);
		else
			simple_send_no_free(srv, client_bis->id, STANDARD_FORK_ANSWER_CURRENT);
	}
}

void	client_tick(t_srv *srv, t_list *player_list)
{
	t_list		*current;
	t_client	*client;
	int			i;

	i = 0;
	current = player_list;
	while (current)
	{
		client = current->content;
		if (client->buffer[0].command == COMMAND_INCANTATION && client->buffer[0].cooldown == 300)
		{
			for (t_list *cc = player_list; cc; cc = cc->next)
			{
				setup_ritual_client(srv, client, cc->content);
			}
			send_to_all_moniteur(srv, moniteur_pic(srv->world, client));
		}
		else if (client->buffer[0].command == COMMAND_FORK && client->buffer[0].cooldown == 42)
		{
			send_to_all_moniteur(srv, moniteur_pfk(client));
		}
		if (client->buffer[0].cooldown > 0 && !client->in_incantation)
			client->buffer[0].cooldown -= 1;
		else
		{
			if (client->buffer[0].command != COMMAND_NONE)
			{
				treat_command(srv, client, i);
			}
		}
		current = current->next;
		if (client->team_name && !is_special_team_member(client) && !(srv->param->flags & FLAG_NOHUNGER))
		{
			if (client->hunger > 0)
				client->hunger--;
			else if (client->ressource[FOOD] > 0)
			{
				client->ressource[FOOD]--;
				client->hunger = MAX_HUNGER;
			}
			else
				kill_player(srv, client);
		}
		++i;
	}

}

void	game_tick(t_srv *srv)
{
	srv->frame_nbr += 1;
	if (can_print(srv->param, LOG_TICK))
		printf("%ld:TICK!!\n", srv->frame_nbr);
	client_tick(srv, srv->world->client_list);
	if (srv->param->generation_frequency != 0 && srv->frame_nbr % srv->param->generation_frequency == 0)
	{
		srv->param->generate_function(*srv->world);
		send_to_all_moniteur(srv, moniteur_mct(srv->world));
	}
	egg_tick(srv, srv->world->egg_list);
}
