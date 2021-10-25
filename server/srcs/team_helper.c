/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   team_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 10:45:04 by selver            #+#    #+#             */
/*   Updated: 2021/10/25 10:01:47 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "functions.h"

static void	welcome_moniteur(t_srv *srv, int id)
{
	char		*msg;
	t_client	*c;

	c = get_current_client(srv, id);
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

	c = get_current_client(srv, id);
	if (!ft_strcmp(team_name, "GRAPHIC"))
		welcome_moniteur(srv, id);
	current = srv->param->team_list;
	while (current)
	{
		team = current->content;
		if (!ft_strcmp(team->team_name, team_name))
		{
			lstsize = ft_lst_size(team->team_clients);
			if (lstsize >= srv->param->allowed_clients_amount)
				return (0);
			ft_lst_append(&team->team_clients, ft_lstgetbypos(srv->world->client_list, id));
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
