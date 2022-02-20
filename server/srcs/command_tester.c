/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tester.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 08:39:43 by jayache           #+#    #+#             */
/*   Updated: 2022/02/20 09:59:12 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	parse_command_set(t_srv *srv, t_client *tester, char *command)
{
	t_client	*target;
	int			arg;
	if (!strncmp("pdi #", command, 5))
	{
		//TODO: check args
		arg = atoi(command + 5);
		target = get_client_by_id(srv, arg);
		if (target)
		{
			if (!is_special_team_member(target))
				kill_player(srv, target);
			else if (target->id != tester->id)
				ft_client_exit(srv, target->id);
			simple_send(srv, tester->id, strdup("ok\n"));
			if (target->id == tester->id)
				ft_client_exit(srv, target->id);
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
	if (!strncmp("pin #", command, 5))
	{
		//TODO: check args
		arg = atoi(command + 5);
		target = get_client_by_id(srv, arg);
		if (target)
		{
			if (strstr(command, " clear"))
			{
				ft_bzero(target->ressource, 7 * sizeof(int));
				target->hunger = 0;
				simple_send(srv, tester->id, strdup("ok\n"));
			}
			else
				simple_send(srv, tester->id, strdup("sbp\n"));
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
	if (!strncmp("ppo #", command, 5))
	{
		//TODO: check args
		arg = atoi(command + 5);
		char **args = split_args(command, 3);
		if (args)
		{
			target = get_client_by_id(srv, arg);
			if (target)
			{
				target->p_x = atoi(args[2]) % srv->param->world_width;
				target->p_y = atoi(args[3]) % srv->param->world_height;
				target->orientation = atoi(args[4]) % 4;
			}
			else
				simple_send(srv, tester->id, strdup("sbp\n"));
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
}

