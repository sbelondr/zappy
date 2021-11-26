/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:57:42 by sbelondr          #+#    #+#             */
/*   Updated: 2021/11/26 16:08:00 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "functions.h"

void ft_client_exit(t_srv *srv, int sd, int i)
{
	getpeername(sd, (struct sockaddr *)&(srv->address),
			(socklen_t *)&(srv->addrlen));
	red();
	t_client *c = get_client_by_id(srv, i);
	if (ft_strequ(c->team_name, "GRAPHIC"))
		c->team_name = NULL;
	printf(ERROR_CLIENT_EXIT, srv->client_sck[i]);
	reset();
	close(sd);
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
		else if (ft_strcmp(c->team_name, "GRAPHIC"))
			send_to_all_moniteur(srv, moniteur_pnw(c));
	}
	else if (!ft_strcmp(c->team_name, "MONITEUR"))
	{
		
	}
	else if (!ft_strcmp(buf, "droite"))
		append_command(c, new_command(COMMAND_DROITE, "", 7));
	else if (!ft_strcmp(buf, "gauche"))
		append_command(c, new_command(COMMAND_GAUCHE, "", 7));
	else if (!ft_strcmp(buf, "avance"))
		append_command(c, new_command(COMMAND_AVANCE, "", 7));
	else if (!ft_strcmp(buf, "voir"))
		append_command(c, new_command(COMMAND_VOIR, "", 7));
	else if (!ft_strcmp(buf, "fork"))
		append_command(c, new_command(COMMAND_FORK, "", 42));
	else if (!ft_strcmp(buf, "inventaire"))
		append_command(c, new_command(COMMAND_INVENTAIRE, "", 1));
	else if (!ft_strncmp(buf, "broadcast", 9))
	{
		char **arr = ft_strsplit(buf, ' ');
		append_command(c, new_command(COMMAND_BROADCAST, arr[1], 7));
		free(arr[0]);
		free(arr);
	}
	else if (!ft_strncmp(buf, "pose", 4))
	{
		char **arr = ft_strsplit(buf, ' ');
		append_command(c, new_command(COMMAND_POSER, arr[1], 7));
		free(arr[0]);
		free(arr);
	}
	else if (!ft_strncmp(buf, "prendre", 7))
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
