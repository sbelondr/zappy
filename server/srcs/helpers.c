/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 10:50:47 by selver            #+#    #+#             */
/*   Updated: 2022/02/20 15:38:12 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

//Returns an array of string, with check to ensure it has expected elements
//If it is impossible, returns NULL
char	**split_args(char *str, int expected)
{
	int		cnt;
	char	**ret;

	cnt = 0;
	for (int i = 0; str[i]; ++i)
		cnt += (str[i] == ' ');
	if (cnt != expected)
	{
		return (NULL);
	}
	ret = ft_strsplit(str, ' ');
	if (!ret)
		return (NULL);
	for (int i = 0; i < expected + 1; ++i)
	{
		if (!ret[i])
		{
			//TODO: free
			return (NULL);
		}
	}
	return (ret);
}
int		is_special_team_member(t_client *client)
{
	return (!strcmp(client->team_name, GRAPHIC_TEAM) ||
			!strcmp(client->team_name, TESTER_TEAM));
}

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
	void	mdel(t_egg *a) { (void)a; }
	send_to_all_moniteur(srv, moniteur_edi(egg));
	ft_lstdelbyval(&srv->world->egg_list, egg, mcmp, mdel);
	team = get_team_by_name(srv->world, egg->team_name);
	ft_lstdelbyval(&team->team_eggs, egg, mcmp, mdel);
	free(egg->team_name);
	free(egg);
	printf("An egg died!\n");
}

void	kill_player(t_srv *srv, t_client *client)
{
	printf("Client #%d died!\n", client->id);
	simple_send(srv, client->id, strdup("mort\n"));
	send_to_all_moniteur(srv, moniteur_pdi(client));
	ft_client_exit(srv, client->id);
}
