/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 08:15:57 by jayache           #+#    #+#             */
/*   Updated: 2022/03/24 10:04:35 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	parse_command_moniteur(t_srv *srv, t_client *c, char *buf)
{
	t_client	*target;
	int			args[10];
	int			error;

	if (!strcmp(buf, "msz"))
		simple_send(srv, c->id, moniteur_msz(srv->world));
	else if (!strcmp(buf, "mct"))
		simple_send(srv, c->id, moniteur_mct(srv->world));
	else if (!strcmp(buf, "tna"))
		simple_send(srv, c->id, moniteur_tna(srv->world));
	else if  (!strcmp(buf, "mac"))
		simple_send(srv, c->id, moniteur_mac(srv->world));
	else if  (!strcmp(buf, "tac"))
		simple_send(srv, c->id, moniteur_tac(srv->world));
	else if  (!strcmp(buf, "sgt"))
		simple_send(srv, c->id, moniteur_sgt(srv->world));
	else if  (!strncmp(buf, "sst ", 4))
	{
		error = sscanf(buf, "sst %d", &args[0]);
		if (error >= 0)
		{
			if (args[0] > 0)
			{
				srv->world->params.time_delta = args[0];
				simple_send(srv, c->id, moniteur_sgt(srv->world));
			}
			else
				simple_send(srv, c->id, strdup("sbp\n"));	
		}
		else
			simple_send(srv, c->id, strdup("sbp\n"));	
	}
	else if  (!strncmp(buf, "bct ", 4))
	{
		error = sscanf(buf, "bct %d %d", &args[0], &args[1]);
		if (error >= 0)
		{
			if (args[0] >= 0 && args[1] >= 0 && args[0] < srv->param->world_width && args[1] < srv->param->world_height)
				simple_send(srv, c->id, moniteur_bct(srv->world, args[0], args[1]));
			else
				simple_send(srv, c->id, strdup("sbp\n"));	
		}
		else
			simple_send(srv, c->id, strdup("sbp\n"));	
	}
	else if  (!strncmp(buf, "pin ", 4))
	{
		error = sscanf(buf, "pin #%d", &args[0]);
		if (error >= 0)
		{
			target = get_client_by_id(srv, args[0]);
			if (args[0] >= 0 && target)
				simple_send(srv, c->id, moniteur_pin(target));
			else
				simple_send(srv, c->id, strdup("sbp\n"));	
		}
		else
			simple_send(srv, c->id, strdup("sbp\n"));	
	}
	else if  (!strncmp(buf, "plv ", 4))
	{
		error = sscanf(buf, "plv #%d", &args[0]);
		if (error >= 0)
		{
			target = get_client_by_id(srv, args[0]);
			if (args[0] >= 0 && target)
				simple_send(srv, c->id, moniteur_plv(target));
			else
				simple_send(srv, c->id, strdup("sbp\n"));
		}
		else
			simple_send(srv, c->id, strdup("sbp\n"));	
	}
	else if  (!strncmp(buf, "ppo ", 4))
	{
		error = sscanf(buf, "ppo #%d", &args[0]);
		if (error >= 0)
		{
			target = get_client_by_id(srv, args[0]);
			if (args[0] >= 0 && target)
				simple_send(srv, c->id, moniteur_ppo(target));
			else
				simple_send(srv, c->id, strdup("sbp\n"));	
		}
		else
			simple_send(srv, c->id, strdup("sbp\n"));	
	}
	else
		simple_send(srv, c->id, ft_strdup("suc\n"));
}

void	connect_client(t_srv *srv, char *buf, t_client *client, int i)
{
	if (!add_to_team(srv, buf, i))
	{
		if (can_print(srv->param, LOG_ERROR) && can_print(srv->param, LOG_CONNEXION))
		{
			set_color(RED, srv->param->flags);
			printf(LOG_REFUSED_CONNEXION, srv->frame_nbr, i, srv->client_sck[i].fd);
			set_color(RESET, srv->param->flags);
		}
		client_exit(srv, i);
	}
	else if (strcmp(client->team_name, GRAPHIC_TEAM) && (strcmp(client->team_name, TESTER_TEAM) || !(srv->param->flags & FLAG_TESTER)))
	{
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

static int is_command(const char *buff, const char *command)
{
	return (!strncmp(buff, command, strlen(command)) && buff[strlen(command)] == ' ');
}

void	command_lexer(t_srv *srv, char *buf, int id)
{
	t_client	*c;
	int			localized;

	c = get_client_by_id(srv, id);
	if (!c)
	{
		if (can_print(srv->param, LOG_ERROR))
		{
			set_color(RED, srv->param->flags);
			printf(LOG_UNDEAD_CLIENT, id);
			set_color(RESET, srv->param->flags);
		}
		return ;
	}
	localized = use_localized_string(srv->param);
	if (c->team_name == NULL)
		connect_client(srv, buf, c, id);
	else if (!strcmp(c->team_name, GRAPHIC_TEAM))
		parse_command_moniteur(srv, c, buf);
	else if (!strcmp(c->team_name, TESTER_TEAM))
		parse_command_tester(srv, c, buf);
	else if (!strcmp(buf, command_name(COMMAND_DROITE, localized)))
		append_command(c, new_command(COMMAND_DROITE, NULL, 7));
	else if (!strcmp(buf, command_name(COMMAND_GAUCHE, localized)))
		append_command(c, new_command(COMMAND_GAUCHE, NULL, 7));
	else if (!strcmp(buf, command_name(COMMAND_AVANCE, localized)))
		append_command(c, new_command(COMMAND_AVANCE, NULL, 7));
	else if (!strcmp(buf, command_name(COMMAND_EXPULSER, localized)))
		append_command(c, new_command(COMMAND_EXPULSER, NULL, 7));
	else if (!strcmp(buf, command_name(COMMAND_VOIR, localized)))
		append_command(c, new_command(COMMAND_VOIR, NULL, 7));
	else if (!strcmp(buf, command_name(COMMAND_INCANTATION, localized)))
		append_command(c, new_command(COMMAND_INCANTATION, NULL, 300));
	else if (!strcmp(buf, command_name(COMMAND_FORK, localized)))
		append_command(c, new_command(COMMAND_FORK, NULL, 42));
	else if (!strcmp(buf, command_name(COMMAND_EXPULSER, localized)))
		append_command(c, new_command(COMMAND_EXPULSER,	NULL, 7));
	else if (!strcmp(buf, command_name(COMMAND_CONNECT_NBR, localized)))
		append_command(c, new_command(COMMAND_CONNECT_NBR, NULL, 0));
	else if (!strcmp(buf, command_name(COMMAND_INVENTAIRE, localized)))
		append_command(c, new_command(COMMAND_INVENTAIRE, NULL, 1));
	else if (is_command(buf, command_name(COMMAND_BROADCAST, localized)))
	{
		char *arg = ft_strdup(buf + strlen(command_name(COMMAND_BROADCAST, localized)) + 1);
		append_command(c, new_command(COMMAND_BROADCAST, arg, 7));
	}
	else if (is_command(buf, command_name(COMMAND_POSER, localized)))
	{
		char **arr = ft_strsplit(buf, ' ');
		if (arr[1] && is_valid_item(arr[1]))
			append_command(c, new_command(COMMAND_POSER, arr[1], 7));
		else
		{
			if (arr[1])
				free(arr[1]);
			append_command(c, new_command(COMMAND_BAD_PARAMETER, NULL, 0));
		}
		free(arr[0]);
		free(arr);
	}
	else if (is_command(buf, command_name(COMMAND_PRENDRE, localized)))
	{
		char **arr = ft_strsplit(buf, ' ');
		if (arr[1] && is_valid_item(arr[1]))
			append_command(c, new_command(COMMAND_PRENDRE, arr[1], 7));
		else
		{
			if (arr[1])
				free(arr[1]);
			append_command(c, new_command(COMMAND_BAD_PARAMETER, NULL, 0));
		}
		free(arr[0]);
		free(arr);
	}
	else
		append_command(c, new_command(COMMAND_UNKNOWN, NULL, 0));
}
