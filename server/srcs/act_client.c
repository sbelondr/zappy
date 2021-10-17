/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:57:42 by sbelondr          #+#    #+#             */
/*   Updated: 2021/10/17 10:05:58 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include "functions.h"

void ft_client_exit(t_srv *srv, int sd, int i)
{
	getpeername(sd, (struct sockaddr *)&(srv->address),
				(socklen_t *)&(srv->addrlen));
	red();
	printf(ERROR_CLIENT_EXIT, srv->client_sck[i]);
	reset();
	close(sd);
	srv->client_sck[i] = 0;
}

t_client *get_current_client(t_srv *srv, int i)
{
	return (ft_lstgetbypos(srv->world->client_list, i)->content);
}

void	ft_lexer(t_srv *srv, char *buf, int i) //HELP: c koi i
{
	t_client	*c;

	c = get_current_client(srv, i);
	if (!ft_strcmp(buf, "droite"))
		append_command(c, new_command(COMMAND_DROITE, "", 7));
	else if (!ft_strcmp(buf, "gauche"))
		append_command(c, new_command(COMMAND_GAUCHE, "", 7));
	else if (!ft_strcmp(buf, "avance"))
		append_command(c, new_command(COMMAND_AVANCE, "", 7));
	else if (!ft_strcmp(buf, "voir"))
		append_command(c, new_command(COMMAND_VOIR, "", 7));
	else if (!ft_strcmp(buf, "inventaire"))
		append_command(c, new_command(COMMAND_INVENTAIRE, "", 1));
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
	buff[valread] = 0;
	green();
	printf("%d ", i);
	printf("[%d] -> %s\n", srv->client_sck[i], buff); //...
	ft_lexer(srv, buff, i);
	reset();
/*	if ((int)send(srv->client_sck[i], msg_receive,
		 strlen(msg_receive), 0) != (int)strlen(msg_receive))
			dprintf(STDERR_FILENO, ERROR_SEND_CLIENT, srv->client_sck[i]);
*/	
}
