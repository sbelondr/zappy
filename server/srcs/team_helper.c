/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 10:45:04 by selver            #+#    #+#             */
/*   Updated: 2022/01/11 10:52:07 by jayache          ###   ########.fr       */
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
		t_client *c = current->content;
		printf("PRESENT: %d\n", c->id);
		if (c->team_name)
		{
		printf("PRESENT\n");
			msg = moniteur_pnw(current->content);
			simple_send(srv, id, msg);
		}
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

int			available_slots(t_srv *srv, t_team *team)
{
	int		lstsize;
	int		remaining_slots;
	int		valid_eggs;
	t_list	*current;
	t_egg	*egg;

	valid_eggs = 0;
	lstsize = ft_lst_size(team->team_clients);
	remaining_slots = srv->param->allowed_clients_amount - lstsize;
	current = team->team_eggs;
	while (current)
	{
		egg = current->content;
		valid_eggs += (egg->maturity <= 0);
		current = current->next;
	}
	return (remaining_slots + valid_eggs);
}

t_egg	*get_first_valid_egg(t_team *team)
{
	//TODO: THAT
	return (NULL);
}

static int	perform_add_to_team(t_srv *srv, t_team *team, t_client *c)
{
	char		*msg;
	t_egg		*egg;
	int			remaining_slots;

	remaining_slots = available_slots(srv, team);
	asprintf(&msg, "%d\n", remaining_slots);
	simple_send(srv, c->id, msg);
	asprintf(&msg, "%d %d\n",
			srv->param->world_width, srv->param->world_height);
	simple_send(srv, c->id, msg);
	if (remaining_slots <= 0)
		return (0);
	ft_lst_append(&team->team_clients, ft_lstnew_no_copy(c, sizeof(t_client)));
	c->team_name = ft_strdup(team->team_name);
	if (ft_lst_size(team->team_clients) > (unsigned int)srv->param->allowed_clients_amount)
	{
		egg = get_first_valid_egg(team);
		c->p_x = egg->p_x;
		c->p_y = egg->p_y;
		egg->used = 1;
	}
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
