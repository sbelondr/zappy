/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:14:09 by selver            #+#    #+#             */
/*   Updated: 2021/03/04 15:55:34 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

long	get_numeric_parameter(char *numstr, int min, int max)
{
	char	*endptr;
	long	result;

	result = strtol(numstr, &endptr, 10);
	if (*endptr || result < min || result > max)
	{
		printf("Invalid numerical parameter\n");
		exit(1);
	}
	else
		return (result);
}

int		is_input_complete(t_param param)
{
	if (!param.port || !param.world_width || !param.world_height)
	{
		printf("Missng parameters\n");
		exit(1);
	}
	if (!param.time_delta || !param.allowed_clients_amount)
	{
		printf("Missng parameters\n");
		exit(1);
	}
	if (!param.team_list || !param.team_list->next)
	{
		printf("Missng parameters\n");
		exit(1);
	}
	return (0);
}

t_param	parse_input(int ac, char **av)
{
	t_param param;
	t_team_list *current;

	bzero(&param, sizeof(t_param));
	for (int i = 1; i < ac; i++) //Ya plus de norme nique toi
	{
		if (i + 1 >= ac)
		{
			printf("Error: unexpected end of argument: %s\n", av[i]);
			exit(1);
		}
		if (!strcmp(av[i], "-t"))
			param.time_delta = get_numeric_parameter(av[++i], 1, 15000);
		else if (!strcmp(av[i], "-p"))
			param.port = get_numeric_parameter(av[++i], 1, 15000);
		else if (!strcmp(av[i], "-x"))
		{
			param.world_width = get_numeric_parameter(av[++i], 1, 15000);
		}
		else if (!strcmp(av[i], "-y"))
		{
			param.world_height = get_numeric_parameter(av[++i], 1, 15000);
		}
		else if (!strcmp(av[i], "-c"))
		{
			param.allowed_clients_amount = get_numeric_parameter(av[++i], 1, 150);
		}
		else if (!strcmp(av[i], "-n"))
		{
			current = param.team_list;
			param.team_list = malloc(sizeof(t_team_list));
			param.team_list->team_name = av[++i];
			param.team_list->next = current;
		}
	}
	is_input_complete(param);
	return (param);
}

int main(int ac, char **av)
{
	t_param param = parse_input(ac, av);
	t_team_list *current = param.team_list;
	printf("x: %d y:: %d t: %d\n", param.world_width, param.world_height, param.time_delta);
	printf("port: %d allowed clients: %d\n", param.port, param.allowed_clients_amount);
	while (current)
	{
		printf("Team name: %s\n", current->team_name);
		current = current->next;
	}
}
