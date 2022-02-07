/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 08:15:57 by jayache           #+#    #+#             */
/*   Updated: 2022/02/07 08:40:25 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "server.h"

void	parse_command_moniteur(t_srv *srv, t_client *c, char *buf)
{
	if (!strcmp(buf, "msz"))
		simple_send(srv, c->id, moniteur_msz(srv->world));
	else if (!strcmp(buf, "mct"))
		simple_send(srv, c->id, moniteur_mct(srv->world));
	else if (!strcmp(buf, "tna"))
		simple_send(srv, c->id, moniteur_tna(srv->world));
	else if  (!strcmp(buf, "sgt"))
		simple_send(srv, c->id, moniteur_sgt(srv->world));
	else if  (!strncmp(buf, "sst", 3))
	{
		//TODO: CHECK VALIDITY OF ARGS
		char **args = ft_strsplit(buf, ' ');
		srv->world->params.time_delta = atoi(args[1]);
		simple_send(srv, c->id, moniteur_sgt(srv->world));
		free(args[0]);
		free(args[1]);
		free(args);
	}
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
	else if  (!strncmp(buf, "pin", 3))
	{
		//TODO: CHECK VALIDITY OF ARGS
		char **args = ft_strsplit(buf, ' ');
		t_client *c = get_client_by_id(srv, atoi(args[1]));
		simple_send(srv, c->id, moniteur_pin(c));
		free(args[0]);
		free(args[1]);
		free(args);
	}
	else if  (!strncmp(buf, "plv", 3))
	{
		//TODO: CHECK VALIDITY OF ARGS
		char **args = ft_strsplit(buf, ' ');
		t_client *c = get_client_by_id(srv, atoi(args[1]));
		simple_send(srv, c->id, moniteur_plv(c));
		free(args[0]);
		free(args[1]);
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
			ft_client_exit(srv, i);
			red();
			printf("Closing connection to #%d\n", srv->client_sck[i]);
			reset();
		}
		else if (strcmp(c->team_name, "GRAPHIC"))
		{
			printf("%ld: %s successfully connected \n", srv->frame_nbr, c->team_name);
			send_to_all_moniteur(srv, moniteur_pnw(c));
		}
	}
	else if (!strcmp(c->team_name, "MONITEUR"))
		parse_command_moniteur(srv, c, buf);
	else if (!strcmp(buf, "droite"))
		append_command(c, new_command(COMMAND_DROITE, NULL, 7));
	else if (!strcmp(buf, "gauche"))
		append_command(c, new_command(COMMAND_GAUCHE, NULL, 7));
	else if (!strcmp(buf, "avance"))
		append_command(c, new_command(COMMAND_AVANCE, NULL, 7));
	else if (!strcmp(buf, "voir"))
		append_command(c, new_command(COMMAND_VOIR, NULL, 7));
	else if (!strcmp(buf, "incantation"))
		append_command(c, new_command(COMMAND_INCANTATION, NULL, 300));
	else if (!strcmp(buf, "fork"))
		append_command(c, new_command(COMMAND_FORK, NULL, 42));
	else if (!strcmp(buf, "expulse"))
		append_command(c, new_command(COMMAND_EXPULSER,	NULL, 7));
	else if (!strcmp(buf, "connect_nbr"))
		append_command(c, new_command(COMMAND_CONNECT_NBR, NULL, 0));
	else if (!strcmp(buf, "inventaire"))
		append_command(c, new_command(COMMAND_INVENTAIRE, NULL, 1));
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
		append_command(c, new_command(COMMAND_UNKNOWN, NULL, 0));
}
