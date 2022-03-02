/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 10:13:21 by selver            #+#    #+#             */
/*   Updated: 2022/03/02 10:56:00 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

t_client	*new_client(int id)
{
	t_client	*ret;

	ret = ft_memalloc(sizeof(t_client));
	ft_bzero(ret->ressource, sizeof(int) * 7);
	ret->id = id;
	ret->lvl = 1;
	ret->ressource[FOOD] = 10;
	return (ret);
}

int		same_position(t_client *a, t_client *b)
{
	return (a->p_x == b->p_x && a->p_y == b->p_y);
}

t_client *get_client_by_id(t_srv *srv, int id)
{
	t_list	*current;

	current = srv->world->client_list;
	while (current)
	{
		if (((t_client*)current->content)->id == id)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

int		is_special_team_member(t_client *client)
{
	return (!client->team_name || 
			!strcmp(client->team_name, GRAPHIC_TEAM) ||
			!strcmp(client->team_name, TESTER_TEAM));
}

void	kill_player(t_srv *srv, t_client *client)
{
	if (can_print(srv->param, LOG_PLAYERDEATH))
	{
		cyan();
		printf("%ld: Client #%d died!\n", srv->frame_nbr, client->id);
		reset();
	}
	simple_send(srv, client->id, strdup("mort\n"));
	send_to_all_moniteur(srv, moniteur_pdi(client));
	ft_client_exit(srv, client->id);
}
