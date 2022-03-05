/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:14:09 by selver            #+#    #+#             */
/*   Updated: 2022/03/05 13:11:48 by jayache          ###   ########.fr       */
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

static	int	is_option(char *argument, char *shortform, char *longform)
{
	int	ret;

	ret = 0;
	if (shortform)
		ret |= !strcmp(argument, shortform);
	if (longform)
		ret |= !strcmp(argument, longform);
	return (ret);
}

t_param	parse_input(int ac, char **av)
{
	t_param param;

	bzero(&param, sizeof(t_param));
	param.team_hard_limit = 500;
	param.allowed_logs = LOG_RECEIVE | LOG_SEND | LOG_CONNEXION;
	param.generate_function = generate_ressource_standard;
	param.generation_frequency = 1000;
	for (int i = 1; i < ac; i++) //Ya plus de norme nique toi
	{
		if (is_option(av[i], "-v", "--verification"))
			param.flags |= FLAG_TESTER;
		else if (is_option(av[i], "-h", "--help"))
			usage();
		else if (is_option(av[i], "-H", "--hunger"))
			param.flags |= FLAG_NOHUNGER;
		else if (is_option(av[i], "-T", "--ticks"))
			param.allowed_logs |= LOG_TICK;
		else if (is_option(av[i], "-s", "--silent"))
			param.allowed_logs = 0;
		else if (i + 1 >= ac)
		{
			printf("Error: unexpected end of argument: %s\n", av[i]);
			usage();
			exit(1);
		}
		else if (is_option(av[i], "-t", "--time"))
			param.time_delta = get_numeric_parameter(av[++i], 1, 15000);
		else if (is_option(av[i], "-p", "--port"))
			param.port = get_numeric_parameter(av[++i], 1, 15000);
		else if (is_option(av[i], "-x", "--width"))
			param.world_width = get_numeric_parameter(av[++i], 5, 15000);
		else if (is_option(av[i], "-y", "--height"))
			param.world_height = get_numeric_parameter(av[++i], 5, 15000);
		else if (is_option(av[i], "-G", "--gen-frequency"))
			param.generation_frequency = get_numeric_parameter(av[++i], 0, 100000);
		else if (is_option(av[i], "-c", "--clients-allowed"))
			param.allowed_clients_amount = get_numeric_parameter(av[++i], 1, 150);
		else if (is_option(av[i], "-m", "--max-clients"))
			param.team_hard_limit = get_numeric_parameter(av[++i], 1, 1000);
		else if (is_option(av[i], "-n", "--name"))
		{
			do
			{
				t_team tmp = new_team(av[++i]);
				ft_lstadd(&param.team_list, ft_lstnew(&tmp, sizeof(t_team)));
			} while (ac > i + 1 && av[i + 1][0] != '-');
		}
		else if (is_option(av[i], "-g", "--gen-function"))
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
