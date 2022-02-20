/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tester.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 08:39:43 by jayache           #+#    #+#             */
/*   Updated: 2022/02/20 16:35:54 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	parse_command_set(t_srv *srv, t_client *tester, char *command)
{
	t_client	*target;
	int			target_id;
	int			arg[10];
	int			error;

	if (!strncmp("pdi #", command, 5))
	{
		//TODO: check args
		target_id = atoi(command + 5);
		target = get_client_by_id(srv, target_id);
		if (target)
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
			else
			{
				ft_client_exit(srv, target->id);
			}
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
	if (!strncmp("pin #", command, 5))
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
	if (!strncmp("ppo #", command, 5))
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
				simple_send(srv, tester->id, strdup("ok\n"));
			}
			else
				simple_send(srv, tester->id, strdup("sbp\n"));
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
}

