/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:57:42 by sbelondr          #+#    #+#             */
/*   Updated: 2022/01/10 14:42:42 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "functions.h"

//TODO: check command args and free
//TODO: les clients sont en double dans la liste??
void ft_client_exit(t_srv *srv, int sd, int i)
{
	t_client	*client;
	t_team		*team;

	getpeername(sd, (struct sockaddr *)&(srv->address),
			(socklen_t *)&(srv->addrlen));
	srv->client_sck[i] = 0;
	int	mcmp(t_client *a, t_client *b)
	{
		printf("%d == %d\n", a->id, b->id);
		return a->id - b->id;
	}
	void	mdel(t_client *a) {}
	client =  get_client_by_id(srv, i);
	ft_lstdelbyval(&srv->world->client_list, client, mcmp, mdel);
	team = get_team_by_name(srv->world, client->team_name);
	ft_lstdelbyval(&team->team_clients, client, mcmp, mdel);
	free(client);
	red();
	printf(ERROR_CLIENT_EXIT, srv->client_sck[i]);
	reset();
	close(sd);
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

void	parse_command_moniteur(t_srv *srv, t_client *c, char *buf)
{
	if (!strcmp(buf, "msz"))
		simple_send(srv, c->id, moniteur_msz(srv->world));
	else if (!strcmp(buf, "mct"))
		simple_send(srv, c->id, moniteur_mct(srv->world));
	else if (!strcmp(buf, "tna"))
		simple_send(srv, c->id, moniteur_tna(srv->world));
	else if  (!strncmp(buf, "bct", 3))
	{
		//TODO: CHECK VALIDITY OF ARGS
		char **args = ft_strsplit(buf, ' ');
		simple_send(srv, c->id, moniteur_bct(srv->world, atoi(args[1]), atoi(args[2])));
		free(args[0]);
		free(args[1]);
		free(args[2]);
		free(args);
	}
	else if  (!strncmp(buf, "ppo", 3))
	{
		//TODO: CHECK VALIDITY OF ARGS
		char **args = ft_strsplit(buf, ' ');
		t_client *c = get_client_by_id(srv, atoi(args[1]));
		simple_send(srv, c->id, moniteur_ppo(c));
		free(args[0]);
		free(args[1]);
		free(args);
	}
	else
		simple_send(srv, c->id, ft_strdup("suc\n"));
}

void	ft_lexer(t_srv *srv, char *buf, int i)
{
	t_client	*c;

	c = get_client_by_id(srv, i);
	if (c->team_name == NULL)
	{
		//check team
		printf("NO TEAM\n");
		if (!add_to_team(srv, buf, i))
		{
			//break connection
		}
		else if (strcmp(c->team_name, "GRAPHIC"))
			send_to_all_moniteur(srv, moniteur_pnw(c));
	}
	else if (!strcmp(c->team_name, "MONITEUR"))
		parse_command_moniteur(srv, c, buf);
	else if (!strcmp(buf, "droite"))
		append_command(c, new_command(COMMAND_DROITE, "", 7));
	else if (!strcmp(buf, "gauche"))
		append_command(c, new_command(COMMAND_GAUCHE, "", 7));
	else if (!strcmp(buf, "avance"))
		append_command(c, new_command(COMMAND_AVANCE, "", 7));
	else if (!strcmp(buf, "voir"))
		append_command(c, new_command(COMMAND_VOIR, "", 7));
	else if (!strcmp(buf, "incantation"))
		append_command(c, new_command(COMMAND_INCANTATION, "", 300));
	else if (!strcmp(buf, "fork"))
		append_command(c, new_command(COMMAND_FORK, "", 42));
	else if (!strcmp(buf, "expulse"))
		append_command(c, new_command(COMMAND_EXPULSER,	"", 7));
	else if (!strcmp(buf, "inventaire"))
		append_command(c, new_command(COMMAND_INVENTAIRE, "", 1));
	else if (!ft_strncmp(buf, "broadcast", 9))
	{
		char **arr = ft_strsplit(buf, ' ');
		append_command(c, new_command(COMMAND_BROADCAST, arr[1], 7));
		free(arr[0]);
		free(arr);
	}
	else if (!strncmp(buf, "pose", 4))
	{
		char **arr = ft_strsplit(buf, ' ');
		append_command(c, new_command(COMMAND_POSER, arr[1], 7));
		free(arr[0]);
		free(arr);
	}
	else if (!strncmp(buf, "prendre", 7))
	{
		char **arr = ft_strsplit(buf, ' ');
		append_command(c, new_command(COMMAND_PRENDRE, arr[1], 7));
		free(arr[0]);
		free(arr);
	}
	else
		append_command(c, new_command(COMMAND_UNKNOWN, "", 0));
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
	printf("%d ", i);
	printf("[%d] -> %s\n", srv->client_sck[i], buff); //...
	ft_lexer(srv, buff, i);
	reset();
}
