/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tester.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 08:39:43 by jayache           #+#    #+#             */
/*   Updated: 2022/03/04 18:00:49 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

static int	parse_int_parameters(char *str, int nb, int *args)
{
	char	**array;
	int		total;

	array = ft_strsplit(str, ' ');
	total = 0;
	if (!array)
		return (-1);
	for (int i = 0; array[i]; ++i)
	{
		if (!ft_strisnumeric(array[i]))
			goto freeerror;
		args[i] = atoi(array[i]);
		total++;
	}
	if (total != nb)
		goto freeerror;
	return (nb);

freeerror:
	for (int i = 0; array[i]; ++i)
		free(array[i]);
	free(array);
	return (-1);
}

static void	kill_any_client(t_srv *srv, t_client *target, t_client *tester)
{
	if (!is_special_team_member(target))
	{
		kill_player(srv, target);
	}
	else if (target->id != tester->id)
	{
		ft_client_exit(srv, target->id);
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
	else if (!strncmp("ppo ", command, 4))
	{
		error = parse_int_parameters(command + 5, 4, arg);
		if (error >= 0)
		{
			target = get_client_by_id(srv, arg[0]);
			if (target && arg[3] > 0 && arg[3] < 5 && arg[1] >= 0 && arg[2] >= 0)
			{
				target->p_x = arg[1] % srv->param->world_width;
				target->p_y = arg[2] % srv->param->world_height;
				target->orientation = arg[3] - 1; 
				send_to_all_moniteur(srv, moniteur_ppo(target));
				simple_send(srv, tester->id, strdup("ok\n"));
			}
			else
				simple_send(srv, tester->id, strdup("sbp\n"));
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
	else if (!strncmp(command, "sst ", 4))
	{
		error = sscanf(command, "sst %d", &arg[0]);
		if (error >= 0 && arg[0] > 0)
		{
			srv->world->params.time_delta = arg[0];
			simple_send(srv, tester->id, moniteur_sgt(srv->world));
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
	else if (!strncmp(command, "mac ", 4))
	{
		error = sscanf(command, "mac %d", &arg[0]);
		if (error >= 0 && arg[0] > 0)
		{
			srv->world->params.team_hard_limit = arg[0];
			simple_send(srv, tester->id, strdup("ok\n"));
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
	else if (!strncmp(command, "tac ", 4))
	{
		error = sscanf(command, "tac %d", &arg[0]);
		if (error >= 0 && arg[0] > 0)
		{
			srv->world->params.allowed_clients_amount = arg[0];
			simple_send(srv, tester->id, strdup("ok\n"));
		}
		else
			simple_send(srv, tester->id, strdup("sbp\n"));
	}
	else if (!strncmp("mct ", command, 4))
	{
		if (strstr(command, " clear"))
		{
			for (int x = 0; x < srv->param->world_width; ++x)
				for (int y = 0; y < srv->param->world_height; ++y)
				{
					ft_bzero(get_case(srv->world, x, y), 7 * sizeof(int));
					send_to_all_moniteur(srv, moniteur_bct(srv->world, x, y));
				}
			simple_send(srv, tester->id, strdup("ok\n"));
		}
		else
		{
			error = sscanf(command, "mct %d %d %d %d %d %d %d", &arg[2], &arg[3], &arg[4], &arg[5], &arg[6], &arg[7],&arg[8]);
			if (error >= 0)
			{
				for (int x = 0; x < srv->param->world_width;++x)
					for (int y = 0; y < srv->param->world_height;++y)
					{
						int *pos = get_case(srv->world, x, y);
						pos[FOOD] = arg[2];
						pos[LINEMATE] = arg[3];
						pos[DERAUMERE] = arg[4];
						pos[SIBUR] = arg[5];
						pos[LAMENDIANE] = arg[6];
						pos[PHIRAS] = arg[7];
						pos[THYSTAME] = arg[8];
						send_to_all_moniteur(srv, moniteur_bct(srv->world, arg[0], arg[1]));
					}
				simple_send(srv, tester->id, strdup("ok\n"));
			}
			else
				simple_send(srv, tester->id, strdup("sbp\n"));
		}
	}
	else if (!strncmp("bct ", command, 4))
	{
		if (strstr(command, " clear"))
		{
			error = sscanf(command, "bct %d %d clear",  &arg[0], &arg[1]);
			if (error >= 0)
			{
				ft_bzero(get_case(srv->world, arg[0], arg[1]), 7 * sizeof(int));
				send_to_all_moniteur(srv, moniteur_bct(srv->world, arg[0], arg[1]));
				simple_send(srv, tester->id, strdup("ok\n"));
			}
			else
				simple_send(srv, tester->id, strdup("sbp\n"));
		}
		else
		{
			//error = parse_int_parameters(command, 9, arg);
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
	}
	else
		simple_send(srv, tester->id, strdup("suc\n"));
}

