/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:57:42 by sbelondr          #+#    #+#             */
/*   Updated: 2022/03/24 10:04:19 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int	mcmp(t_client *a, t_client *b) { 	return a->id - b->id; }
static void	mdel(t_client *a) { (void)a; }

void client_exit(t_srv *srv, int id)
{
	t_client	*client;
	t_team		*team;


	client = get_client_by_id(srv, id);
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
		set_color(PURPLE, srv->param->flags);
		printf(LOG_CLIENTS_LEFT, ft_lst_size(srv->world->client_list));
		set_color(RESET, srv->param->flags);
	}
	close(srv->client_sck[id].fd);
	srv->client_sck[id].fd = 0;
}

//Delete the newline on the string/cut the string via newline, returns the number of lines found
static int		delete_newline(char *buff)
{
	int		size;
	int		occurence;

	occurence = 0;
	size = strlen(buff);
	for (int i = 0; i < size; ++i)
	{
		if (buff[i] == '\n')
		{
			occurence++;
			buff[i] = '\0';
		}
	}
	return (occurence);
}


void client_sent_data(t_srv *srv, char *buff, int valread, int i)
{
	int	commands;
	int	offset;

	if (valread < 0)
		return ;
	buff[valread] = 0;

	commands = delete_newline(buff);
	if (commands == 0 && can_print(srv->param, LOG_ERROR))
	{
		set_color(RED, srv->param->flags);
		printf(LOG_INCOMPLETE_COMMAND, srv->frame_nbr, srv->client_sck[i].fd, i, buff);
		set_color(RESET, srv->param->flags);
	}
	offset = 0;
	for (int x = 0; x < commands; ++x)
	{
		if (can_print(srv->param, LOG_RECEIVE))
		{
			set_color(GREEN, srv->param->flags);
			printf("%ld: [%d] -> %s\n", srv->frame_nbr, srv->client_sck[i].fd, buff); 
			set_color(RESET, srv->param->flags);
		}
		printf("%d\n", i);
		command_lexer(srv, buff + offset, i - 1);
		offset = strlen(buff) + 1;
	}
}
