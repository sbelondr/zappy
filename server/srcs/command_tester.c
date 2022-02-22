/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tester.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 08:39:43 by jayache           #+#    #+#             */
/*   Updated: 2022/02/22 13:35:26 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static void	kill_any_client(t_srv *srv, t_client *target, t_client *tester)
{
	if (!is_special_team_member(target))
	{
		kill_player(srv, target);
		simple_send(srv, tester->id, strdup("ok\n"));
	}
	else if (target->id != tester->id)
	{
		ft_client_exit(srv, target->id);
		simple_send(srv, tester->id, strdup("ok\n"));
	}
}

static void	parse_pdi(t_srv *srv, t_client *tester, char *command)
{
	int			target_id;
	t_list		*current;
	t_client	*target;

	if (!strcmp("all", command))
	{
		current = srv->world->client_list;
		while (current)
		{
			target = current->content;
			current = current->next;
			kill_any_client(srv, target, tester);
		}
		ft_client_exit(srv, tester->id);
	}
	else
	{
		target_id = atoi(command);
		target = get_client_by_id(srv, target_id);
		if (target)
		{
			kill_any_client(srv, target, tester);
			simple_send(srv, tester->id, strdup("ok\n"));
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
}

static void	parse_edi(t_srv *srv, t_client *tester, char *command)
{
	t_egg	*target;
	t_list	*current;
	int		target_id;

	if (!strcmp("all", command))
	{
		current = srv->world->egg_list;
		while (current)
		{
			target = current->content;
			current = current->next;
			rotten_egg(srv, target);
		}
		simple_send(srv, tester->id, ft_strdup("ok\n"));
	}
	else
	{
		target_id = atoi(command);
		target = get_egg_by_id(srv->world, target_id);
		if (target)
		{
			rotten_egg(srv, target);
			simple_send(srv, tester->id, ft_strdup("ok\n"));
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
}

void	parse_command_set(t_srv *srv, t_client *tester, char *command)
{
	t_client	*target;
	int			target_id;
	int			arg[10];
	int			error;

	if (!strncmp("pdi ", command, 4))
	{
		parse_pdi(srv, tester, command + 4);
	}
	else if (!strncmp("edi ", command, 4))
	{
		parse_edi(srv, tester, command + 4);
	}
	else if (!strncmp("pin #", command, 5))
	{
		//TODO: check args
		target_id = atoi(command + 5);
		target = get_client_by_id(srv, target_id);
		if (target)
		{
			if (strstr(command, " clear"))
			{
				ft_bzero(target->ressource, 7 * sizeof(int));
				target->hunger = 0;
				simple_send(srv, tester->id, strdup("ok\n"));
			}
			else
			{
				error = sscanf(command, "pin #%d %d %d %d %d %d %d %d", &arg[0], &arg[1], &arg[2], &arg[3], &arg[4], &arg[5], &arg[6], &arg[7]);
				if (error < 0)
				{
					simple_send(srv, tester->id, strdup("sbp\n"));
					return ;
				}
				target->ressource[FOOD] = arg[1];
				target->ressource[LINEMATE] = arg[2];
				target->ressource[DERAUMERE] = arg[3];
				target->ressource[SIBUR] = arg[4];
				target->ressource[LAMENDIANE] = arg[5];
				target->ressource[PHIRAS] = arg[6];
				target->ressource[THYSTAME] = arg[7];
				simple_send(srv, tester->id, strdup("ok\n"));
			}
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
	else if (!strncmp("ppo #", command, 5))
	{
		//TODO: check args
		error = sscanf(command, "ppo #%d %d %d %d", &arg[0], &arg[1], &arg[2], &arg[3]);
		if (error >= 0)
		{
			target = get_client_by_id(srv, arg[0]);
			if (target)
			{
				target->p_x = arg[1] % srv->param->world_width;
				target->p_y = arg[2] % srv->param->world_height;
				target->orientation = arg[3] - 1; //TODO: VERIFY UNDERFLOW
				send_to_all_moniteur(srv, moniteur_ppo(target));
				simple_send(srv, tester->id, strdup("ok\n"));
			}
			else
				simple_send(srv, tester->id, strdup("sbp\n"));
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
	else if (!strncmp(command, "tac ", 4))
	{
		error = sscanf(command, "tac %d", &arg[0]);
		if (error >= 0 && arg[0] > 0)
		{
			srv->param->allowed_clients_amount = arg[0];
			simple_send(srv, tester->id, strdup("ok\n"));
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
	else if (!strncmp("bct ", command, 4))
	{
		error = sscanf(command, "bct %d %d %d %d %d %d %d %d %d",  &arg[0], &arg[1], &arg[2], &arg[3], &arg[4], &arg[5], &arg[6], &arg[7],&arg[8]);
		if (error >= 0)
		{
			int *pos = get_case(srv->world, arg[0], arg[1]);
			pos[FOOD] = arg[2];
			pos[LINEMATE] = arg[3];
			pos[DERAUMERE] = arg[4];
			pos[SIBUR] = arg[5];
			pos[LAMENDIANE] = arg[6];
			pos[PHIRAS] = arg[7];
			pos[THYSTAME] = arg[8];
			simple_send(srv, tester->id, strdup("ok\n"));
			send_to_all_moniteur(srv, moniteur_bct(srv->world, arg[0], arg[1]));
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
	else
		simple_send(srv, tester->id, strdup("suc\n"));
}

