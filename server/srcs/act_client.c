/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:57:42 by sbelondr          #+#    #+#             */
/*   Updated: 2022/02/11 10:16:23 by sbelondr         ###   ########.fr       */
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

//	getpeername(srv->client_sck[i], (struct sockaddr *)&(srv->address), //????? pk tu changes l'addresses du serveur?
//			(socklen_t *)&(srv->addrlen));
//	dprintf(STDERR_FILENO, "client_sck: %d\n", srv->client_sck[i]);
	int	mcmp(t_client *a, t_client *b)
	{
		return a->id - b->id;
	}
	void	mdel(t_client *a) { (void)a; }
	client = get_client_by_id(srv, i);
	ft_lstdelbyval(&srv->world->client_list, client, mcmp, mdel);
	if (client->team_name && ft_strcmp(client->team_name, "GRAPHIC"))
	{
		team = get_team_by_name(srv->world, client->team_name);
		ft_lstdelbyval(&team->team_clients, client, mcmp, mdel);
	}
	for (int i = 0; i < 10; ++i)
	{
		if (client->buffer[i].arg)
			free(client->buffer[i].arg);
	}
	if (client->team_name && strcmp(client->team_name, "GRAPHIC"))
		free(client->team_name);
	free(client);
	printf("There is still %ld clients left!\n", ft_lst_size(srv->world->client_list));
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


void ft_client_send_data(t_srv *srv, char *buff, int valread, int i)
{
	if (valread < 0)
		return ;
	buff[valread] = 0;
	if (!delete_newline(buff))
	{
		printf("ERROR: CLIENT DOES NOT RESPECT RFC: '%s'\n", buff);
		exit(1);
	}
	green();
	printf("%ld: [%d] -> %s\n", srv->frame_nbr, srv->client_sck[i], buff); //...
	ft_lexer(srv, buff, i);
	reset();
}
