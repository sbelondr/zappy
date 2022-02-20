/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 08:15:57 by jayache           #+#    #+#             */
/*   Updated: 2022/02/20 09:59:28 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "server.h"


void	parse_command_moniteur(t_srv *srv, t_client *c, char *buf)
{
	t_client	*target;
	char		**args;
	int			arg1;
	int			arg2;

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
		args = split_args(buf, 1);
		if (args)
		{
			arg1 = atoi(args[1]);
			if (arg1 > 0)
			{
				srv->world->params.time_delta = atoi(args[1]);
				simple_send(srv, c->id, moniteur_sgt(srv->world));
			}
			else
				simple_send(srv, c->id, strdup("sbp\n"));	
			free(args[0]);
			free(args[1]);
			free(args);
		}
		else
			simple_send(srv, c->id, strdup("sbp\n"));	
	}
	else if  (!strncmp(buf, "bct", 3))
	{
		args = split_args(buf, 2);
		if (args)
		{
			arg1 = atoi(args[1]);
			arg2 = atoi(args[2]);
			if (arg1 >= 0 && arg2 >= 0 && arg1 < srv->param->world_width && arg2 < srv->param->world_height)
				simple_send(srv, c->id, moniteur_bct(srv->world, atoi(args[1]), atoi(args[2])));
			else
				simple_send(srv, c->id, strdup("sbp\n"));	
			free(args[0]);
			free(args[1]);
			free(args[2]);
		}
		else
			simple_send(srv, c->id, strdup("sbp\n"));	
		free(args);
	}
	else if  (!strncmp(buf, "pin", 3))
	{
		args = split_args(buf, 1);
		if (args)
		{
			arg1 = atoi(args[1]);
			target = get_client_by_id(srv, arg1);
			if (arg1 >= 0 && target)
				simple_send(srv, c->id, moniteur_pin(target));
			else
				simple_send(srv, c->id, strdup("sbp\n"));	
			free(args[0]);
			free(args[1]);
			free(args);
		}
		else
			simple_send(srv, c->id, strdup("sbp\n"));	
	}
	else if  (!strncmp(buf, "plv", 3))
	{
		args = split_args(buf, 1);
		if (args)
		{
			arg1 = atoi(args[1]);
			target = get_client_by_id(srv, arg1);
			if (arg1 >= 0 && target)
				simple_send(srv, c->id, moniteur_plv(target));
			else
				simple_send(srv, c->id, strdup("sbp\n"));
			free(args[0]);
			free(args[1]);
			free(args);
		}
		else
			simple_send(srv, c->id, strdup("sbp\n"));	
	}
	else if  (!strncmp(buf, "ppo", 3))
	{
		args = split_args(buf, 1);
		if (args)
		{
			arg1 = atoi(args[1] + 1);
			target = get_client_by_id(srv, arg1);
			if (arg1 >= 0 && target)
				simple_send(srv, c->id, moniteur_ppo(target));
			else
				simple_send(srv, c->id, strdup("sbp\n"));	
			free(args[0]);
			free(args[1]);
			free(args);
		}
		else
			simple_send(srv, c->id, strdup("sbp\n"));	
	}
	else
		simple_send(srv, c->id, ft_strdup("suc\n"));
}

void	connect_client(t_srv *srv, char *buf, t_client *client, int i)
{
	printf("NO TEAM\n");
	if (!add_to_team(srv, buf, i))
	{
		red();
		printf("%ld: Connexion refused for SD: #%d\n", srv->frame_nbr, srv->client_sck[i]);
		reset();
		ft_client_exit(srv, i);
	}
	else if (strcmp(client->team_name, GRAPHIC_TEAM) && (strcmp(client->team_name, TESTER_TEAM) && srv->param->flags & FLAG_TESTER))
	{
		printf("%ld: %s successfully connected \n", srv->frame_nbr, client->team_name);
		send_to_all_moniteur(srv, moniteur_pnw(client));
	}
}

void	parse_command_tester(t_srv *srv, t_client *tester, char *buf)
{
	if (!strncmp(buf, "get ", 4))
		parse_command_moniteur(srv, tester, buf + 4);
	else if (!strncmp(buf, "set ", 4))
		parse_command_set(srv, tester, buf + 4);
	else
		simple_send(srv, tester->id, ft_strdup("suc\n"));

}

void	ft_lexer(t_srv *srv, char *buf, int i)
{
	t_client	*c;

	c = get_client_by_id(srv, i);
	if (c->team_name == NULL)
		connect_client(srv, buf, c, i);
	else if (!strcmp(c->team_name, GRAPHIC_TEAM))
		parse_command_moniteur(srv, c, buf);
	else if (!strcmp(c->team_name, TESTER_TEAM))
		parse_command_tester(srv, c, buf);
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
	else if (!ft_strncmp(buf, "broadcast ", 10))
	{
		char *arg = ft_strdup(buf + strlen("broadcast "));
		append_command(c, new_command(COMMAND_BROADCAST, arg, 7));
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
