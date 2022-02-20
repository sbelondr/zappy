/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_tick.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:34:19 by selver            #+#    #+#             */
/*   Updated: 2022/02/20 09:41:43 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	treat_command(t_srv *srv, t_client *client, int client_id)
{
	char *msg;
	size_t ret;

	t_game_action act = get_action_from_enum(client->buffer[0].command);
	msg = act(srv, srv->world, client);
	printf("[%d] <- %s\n", srv->client_sck[client_id], msg);
	ret = send(srv->client_sck[client_id], msg, ft_strlen(msg), MSG_DONTWAIT);
	if (ret != ft_strlen(msg))
		printf("ERROR!! send n'a pas tout envoyé");
	free(msg);
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
			egg->maturity--;
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

void	setup_ritual_client(t_srv *srv, t_client *client, t_client *client_bis)
{
	int	ret;

	if (client_bis->p_x == client->p_x && client_bis->p_y == client->p_y && client->lvl == client_bis->lvl)
	{
		printf("[%d] <- %s\n", srv->client_sck[client_bis->id], "elevation en cours\n");
		if (client_bis->buffer[0].command != COMMAND_INCANTATION)
			client_bis->in_incantation = 1;
		ret = send(srv->client_sck[client_bis->id], "elevation en cours\n", 19, MSG_DONTWAIT);
		if (ret != 19)
			printf("ERROR!! send n'a pas tout envoyé");
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
			send_to_all_moniteur(srv, moniteur_pfk(client));
		if (client->buffer[0].cooldown > 0)
			client->buffer[0].cooldown -= 1;
		else
		{
			if (client->buffer[0].command != COMMAND_NONE)
			{
				treat_command(srv, client, i);
			}
		}
		current = current->next;
		++i;
	}

}

void	game_tick(t_srv *srv)
{
	srv->frame_nbr += 1;
	client_tick(srv, srv->world->client_list);
	if (srv->frame_nbr % 10000 > 0) //TODO: make this a command line parameter
	{
		//		generate_ressource(*srv->world);
	}
	egg_tick(srv, srv->world->egg_list);
}
