/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:14:09 by selver            #+#    #+#             */
/*   Updated: 2022/02/23 09:14:07 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"
#include "functions.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

t_world_state init_world(t_param params);

void	usage(void)
{
	printf(USAGE);
	exit(1);
}

long	get_numeric_parameter(char *numstr, int min, int max)
{
	char	*endptr;
	long	result;

	result = strtol(numstr, &endptr, 10);
	if (*endptr)
	{
		printf("Invalid parameter: Not a number: %s\n", numstr);
		usage();
	}
	else if (result < min)
	{
		printf("Invalid parameter: Number too small: %ld when min size is %d\n", result, min);
		usage();
	}
	else if (result > max)
	{
		printf("Invalid parameter: Number too big: %ld when max size is %d\n", result, max);
		usage();
	}
	return (result);
}

int		is_input_complete(t_param param)
{
	if (!param.port)
	{
		printf("Missing port\n");
		usage();
	}
	if (!param.world_width || !param.world_height)
	{
		printf("Missing parameters\n");
		usage();
	}
	if (!param.time_delta || !param.allowed_clients_amount)
	{
		printf("Missing parameters\n");
		usage();
	}
	if (!param.team_list)
	{
		printf("Missing parameters\n");
		usage();
	}
	return (0);
}

t_team	new_team(char *name)
{
	t_team	team;

	team.team_name = name;
	team.team_clients = NULL;
	team.team_eggs = NULL;
	return (team);
}

t_param	parse_input(int ac, char **av)
{
	t_param param;

	bzero(&param, sizeof(t_param));
	param.team_hard_limit = 500;
	param.generate_function = generate_ressource_standard;
	for (int i = 1; i < ac; i++) //Ya plus de norme nique toi
	{
		if (!strcmp(av[i], "-v"))
			param.flags |= FLAG_TESTER;
		else if (!strcmp(av[i], "-h"))
			usage();
		else if (!strcmp(av[i], "-H"))
			param.flags |= FLAG_NOHUNGER;
		else if (!strcmp(av[i], "-T"))
			param.flags |= FLAG_TICK;
		else if (i + 1 >= ac)
		{
			printf("Error: unexpected end of argument: %s\n", av[i]);
			usage();
			exit(1);
		}
		if (!strcmp(av[i], "-t"))
			param.time_delta = get_numeric_parameter(av[++i], 1, 15000);
		else if (!strcmp(av[i], "-p"))
			param.port = get_numeric_parameter(av[++i], 1, 15000);
		else if (!strcmp(av[i], "-x"))
		{
			param.world_width = get_numeric_parameter(av[++i], 5, 15000);
		}
		else if (!strcmp(av[i], "-y"))
		{
			param.world_height = get_numeric_parameter(av[++i], 5, 15000);
		}
		else if (!strcmp(av[i], "-G"))
		{
			param.generation_frequency = get_numeric_parameter(av[++i], 1, 100000);
		}
		else if (!strcmp(av[i], "-c"))
		{
			param.allowed_clients_amount = get_numeric_parameter(av[++i], 1, 150);
		}
		else if (!strcmp(av[i], "-m"))
		{
			param.team_hard_limit = get_numeric_parameter(av[++i], 1, 1000);
		}
		else if (!strcmp(av[i], "-n"))
		{
			do
			{
				t_team tmp = new_team(av[++i]);
				ft_lstadd(&param.team_list, ft_lstnew(&tmp, sizeof(t_team)));
			} while (ac > i + 1 && av[i + 1][0] != '-');
		}
		else if (!strcmp(av[i], "-g"))
		{
			++i;
			if (!strcmp(av[i], "STANDARD")) {
				param.generate_function = generate_ressource_standard;
			}
			else if (!strcmp(av[i], "UNIFORM")) {
				param.generate_function = generate_ressource_uniform;
			}
			else
				usage();
		}
	}
	is_input_complete(param);
	return (param);
}
