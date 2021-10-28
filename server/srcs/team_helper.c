/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 10:45:04 by selver            #+#    #+#             */
/*   Updated: 2021/10/28 10:09:24 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "functions.h"

int asprintf(char **strp, const char *fmt, ...);

static void	welcome_moniteur(t_srv *srv, int id)
{
	char		*msg;
	t_client	*c;
	t_list		*current;

	c = get_client_by_id(srv, id);
	c->team_name = "GRAPHIC";
	simple_send(srv, id, moniteur_msz(srv->world));
	msg = moniteur_sgt(srv->world);
	simple_send(srv, id, msg);
	msg = moniteur_mct(srv->world);
	simple_send(srv, id, msg);
	msg = moniteur_tna(srv->world);
	simple_send(srv, id, msg);
	current = srv->world->client_list;
	while (current)
	{
		msg = moniteur_pnw(current->content);
		simple_send(srv, id, msg);
		current = current->next;
	}
	current = srv->world->egg_list;
	while (current)
	{
		msg = moniteur_enw(current->content);
		simple_send(srv, id, msg);
		current = current->next;
	}
}

static int	perform_add_to_team(t_srv *srv, t_team *team, t_client *c)
{
	int			lstsize;
	char		*msg;
	int			remaining_slots;

	lstsize = ft_lst_size(team->team_clients);
	remaining_slots = srv->param->allowed_clients_amount - lstsize
		+ ft_lst_size(team->team_eggs);
	asprintf(&msg, "%d\n", remaining_slots);
	simple_send(srv, c->id, msg);
	asprintf(&msg, "%d %d\n",
			srv->param->world_width, srv->param->world_height);
	simple_send(srv, c->id, msg);
	if (remaining_slots <= 0)
		return (0);
	ft_lst_append(&team->team_clients, ft_lstnew(c, sizeof(t_client)));
	c->team_name = ft_strdup(team->team_name);
	return (1);
}

/*
 * Adds a client to a team
 * Returns 0 on failure, 1 on success
 */
int		add_to_team(t_srv *srv, char *team_name, int id)
{
	t_client	*c;
	t_list		*current;
	t_team		*team;

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
			return (perform_add_to_team(srv, team, c));
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
