/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 10:45:04 by selver            #+#    #+#             */
/*   Updated: 2021/10/27 15:37:33 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "functions.h"

static void	welcome_moniteur(t_srv *srv, int id)
{
	char		*msg;
	t_client	*c;
	t_list		*current;

	c = get_client_by_id(srv, id);
	c->team_name = "GRAPHIC";
	msg = moniteur_msz(srv->world);
	simple_send(srv, id, msg);
	free(msg);
	msg = moniteur_sgt(srv->world);
	simple_send(srv, id, msg);
	free(msg);
	msg = moniteur_mct(srv->world);
	simple_send(srv, id, msg);
	free(msg);
	msg = moniteur_tna(srv->world);
	simple_send(srv, id, msg);
	free(msg);
	current = srv->world->client_list;
	while (current)
	{
		msg = moniteur_pnw(current->content);
		simple_send(srv, id, msg);
		free(msg);
		current = current->next;
	}
	current = srv->world->egg_list;
	while (current)
	{
		msg = moniteur_enw(current->content);
		simple_send(srv, id, msg);
		free(msg);
		current = current->next;
	}
}

// returns 0 on failure, 1 on success
/*
 * Adds a client to a team
 */
int		add_to_team(t_srv *srv, char *team_name, int id)
{
	t_client	*c;
	t_list		*current;
	t_team		*team;
	int			lstsize;

	c = get_client_by_id(srv, id);
	if (!ft_strcmp(team_name, "GRAPHIC"))
	{
		welcome_moniteur(srv, id);
		return (1);
	}	
		current = srv->param->team_list;
	while (current)
	{
		team = current->content;
		if (!ft_strcmp(team->team_name, team_name))
		{
			lstsize = ft_lst_size(team->team_clients);
			if (lstsize >= srv->param->allowed_clients_amount)
				return (0);
			ft_lst_append(&team->team_clients, ft_lstnew(c, sizeof(t_client)));
			printf("Appended!\n");
			simple_send(srv, id, "4\n");
			simple_send(srv, id, "10 10\n");
			c->team_name = ft_strdup(team_name);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int		add_egg_to_team(t_world_state *world, char *team_name, int egg_id)
{
	t_egg		*e;
	t_list		*current;
	t_team		*team;

	e = get_egg_by_id(world, egg_id);
	current = world->params.team_list;
	while (current)
	{
		team = current->content;
		if (!ft_strcmp(team->team_name, team_name))
		{
			ft_lst_append(&team->team_eggs, ft_lstnew(e, sizeof(t_egg))); 
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int		remove_from_team(t_srv *srv, t_client *c)
{
	t_list	*current;
	t_team	*team;

	current = srv->param->team_list;
	while (current)
	{
		team = current->content;
		if (!ft_strcmp(team->team_name, c->team_name))
		{
			int simpleequal(t_client *a, t_client *b) { return a != b; }
			void emptydel(t_client *_a) { (void)_a;  }
			ft_lstdelbyval(&team->team_clients, c, simpleequal, emptydel);
			return (1);
		}
		current = current->next;
	}
	return (0);
}
