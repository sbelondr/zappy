/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 10:50:47 by selver            #+#    #+#             */
/*   Updated: 2022/01/18 11:45:14 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
 * Simplified way to call send
 */

void simple_send(t_srv *srv, int id, char *msg)
{
	if ((int)send(srv->client_sck[id], msg, \
			strlen(msg), 0) != (int)strlen(msg))
		dprintf(STDERR_FILENO, ERROR_SEND_CLIENT, \
				srv->client_sck[id]);
	free(msg);
}

t_client *get_current_client(t_srv *srv, int i)
{
	return (ft_lstgetbypos(srv->world->client_list, i)->content);
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

t_egg	*get_egg_by_id(t_world_state *world, int id)
{
	t_list	*current;

	current = world->egg_list;
	while (current)
	{
		if (((t_egg*)current->content)->id == id)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

t_team	*get_team_by_name(t_world_state *world, char *team_name)
{
	t_list	*current;
	t_team	*team;

	current = world->params.team_list;
	while (current)
	{
		team = current->content;
		if (!strcmp(team_name, team->team_name))
			return (team);
		current = current->next;
	}
	return (NULL);
}

void	rotten_egg(t_srv *srv, t_egg *egg)
{
	t_team *team;

	int	mcmp(t_egg *a, t_egg *b) { 	return a->id - b->id; }
	void	mdel(t_egg *a) {}
	send_to_all_moniteur(srv, moniteur_edi(egg));
	ft_lstdelbyval(&srv->world->egg_list, egg, mcmp, mdel);
	team = get_team_by_name(srv->world, egg->team_name);
	ft_lstdelbyval(&team->team_eggs, egg, mcmp, mdel);
	free(egg->team_name);
	free(egg);
	printf("An egg died!\n");
}
