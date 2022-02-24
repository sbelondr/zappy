/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:57:42 by sbelondr          #+#    #+#             */
/*   Updated: 2022/02/23 13:04:16 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "functions.h"

void	remove_from_client_list(t_world_state *world, t_client *client)
{
	t_list		*current;
	t_list		*last;
	t_list		*to_free;
	t_client	*tmp;

	current = world->client_list;
	last = NULL;
	while (current)
	{
		to_free = NULL;
		tmp = current->content;
		if (tmp->id == client->id)
		{
			if (last)
				last->next = current->next;
			else
				world->client_list = current->next;
			to_free = current;
		}
		last = current;
		current = current->next;
		if (to_free)
			free(to_free);
	}
}

void ft_client_exit(t_srv *srv, int i)
{
	t_client	*client;
	t_team		*team;

	int	mcmp(t_client *a, t_client *b) { return a->id - b->id; }
	void	mdel(t_client *a) { (void)a; }

	client = get_client_by_id(srv, i);
	ft_lstdelbyval(&srv->world->client_list, client, mcmp, mdel);
	if (client->team_name && !is_special_team_member(client))
	{
		team = get_team_by_name(srv->world, client->team_name);
		ft_lstdelbyval(&team->team_clients, client, mcmp, mdel);
	}
	clear_commands(client);
	if (client->team_name && !is_special_team_member(client))
		free(client->team_name);
	free(client);
	if (can_print(srv->param, LOG_INFO))
	{
		purple();
		printf("There is still %ld clients left!\n", ft_lst_size(srv->world->client_list));
		reset();
	}
	//shutdown(srv->client_sck[i], SHUT_RD);
	close(srv->client_sck[i]);
	srv->client_sck[i] = 0;
}

//returns 0 if no newline, 1 otherwise
static int		delete_newline(char *buf)
{
	size_t	size;

	size = ft_strlen(buf);
	if (buf[size - 1] != '\n')
		return (0);
	buf[size - 1] = '\0';
	return (1);
}


void ft_client_sent_data(t_srv *srv, char *buff, int valread, int i)
{
	if (valread < 0)
		return ;
	buff[valread] = 0;
	if (!delete_newline(buff))
	{
		printf("ERROR: CLIENT DOES NOT RESPECT RFC: '%s'\n", buff);
		exit(1);
	}
	if (can_print(srv->param, LOG_RECEIVE))
	{
		green();
		printf("%ld: [%d] -> %s\n", srv->frame_nbr, srv->client_sck[i], buff); 
		reset();
	}
	ft_lexer(srv, buff, i);
}
