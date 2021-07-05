/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 20:57:42 by sbelondr          #+#    #+#             */
/*   Updated: 2021/07/05 10:33:31 by selver           ###   ########.fr       */
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

char	*ft_lexer(t_srv *srv, char *buf, int i) //HELP: c koi i
{
	t_client	*c;
	char		*message;

	c = get_current_client(srv, i);
	if (!ft_strcmp(buf, "droite"))
		message = turn_right(srv->world, c);
	else if (!ft_strcmp(buf, "gauche"))
		message = turn_left(srv->world, c);
	else if (!ft_strcmp(buf, "avance"))
		message = avance(srv->world, c);
	else if (!ft_strcmp(buf, "voir"))
		message = action_see_string(srv->world, c);
	else if (!ft_strcmp(buf, "inventaire"))
		message = see_inventaire(srv->world, c);
	else
		message = ft_strdup("???");
	return (message);
}

void ft_client_send_data(t_srv *srv, char *buff, int valread, int i)
{
	char *msg_receive;

	buff[valread] = 0;
	green();
	printf("%d ", i);
	printf("[%d] -> %s\n", srv->client_sck[i], buff); //...
	msg_receive = ft_lexer(srv, buff, i);
	reset();
	if ((int)send(srv->client_sck[i], msg_receive,
		 strlen(msg_receive), 0) != (int)strlen(msg_receive))
			dprintf(STDERR_FILENO, ERROR_SEND_CLIENT, srv->client_sck[i]);
	free(msg_receive);
}
