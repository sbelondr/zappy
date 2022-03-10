/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:14:09 by selver            #+#    #+#             */
/*   Updated: 2022/03/10 11:07:05 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"
#include "functions.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

t_world_state init_world(t_param params);

void	usage(int error)
{
	if (error)
		fprintf(stderr, USAGE);
	else
		printf(USAGE);
	exit(error);
}

long	get_numeric_parameter(char *numstr, int min, int max)
{
	char	*endptr;
	long	result;

	result = strtol(numstr, &endptr, 10);
	if (*endptr)
	{
		fprintf(stderr, ERROR_INV_PARAM_NAN, numstr);
		usage(1);
	}
	else if (result < min)
	{
		fprintf(stderr, ERROR_INV_PARAM_TOO_SMALL, result, min);
		usage(1);
	}
	else if (result > max)
	{
		fprintf(stderr, ERROR_INV_PARAM_TOO_BIG, result, max);
		usage(1);
	}
	return (result);
}

int		is_input_complete(t_param param)
{
	int success = 1;
	if (!param.port)
	{
		fprintf(stderr, ERROR_MISSING_PARAM_PORT);
		success = 0;
	}
	if (!param.world_width)
	{
		fprintf(stderr, ERROR_MISSING_PARAM_WIDTH);
		success = 0;
	}
	if (!param.world_height)
	{
		fprintf(stderr, ERROR_MISSING_PARAM_HEIGHT);
		success = 0;
	}
	if (!param.time_delta)
	{
		fprintf(stderr, ERROR_MISSING_PARAM_DELTA);
		success = 0;
	}
	if (!param.allowed_clients_amount)
	{
		fprintf(stderr, ERROR_MISSING_PARAM_ACA);
		success = 0;
	}
	if (!param.team_list)
	{
		fprintf(stderr, ERROR_MISSING_PARAM_TEAM);
		success = 0;
	}
	return (success);
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
	param.flags |= FLAG_COLOR;
	for (int i = 1; i < ac; i++) //Ya plus de norme nique toi
	{
		if (is_option(av[i], "-v", "--verification"))
			param.flags |= FLAG_TESTER;
		else if (is_option(av[i], "-h", "--help"))
			usage(0);
		else if (is_option(av[i], "-H", "--hunger"))
			param.flags |= FLAG_NOHUNGER;
		else if (is_option(av[i], "-s", "--silent"))
			param.allowed_logs = 0;
		else if (is_option(av[i], "-V", "--verbose"))
			param.allowed_logs = 0xFFFF;
		else if (is_option(av[i], NULL, "--print-ticks"))
			param.allowed_logs |= LOG_TICK;
		else if (is_option(av[i], NULL, "--no-print-ticks"))
			param.allowed_logs &= ~LOG_TICK;
		else if (is_option(av[i], NULL, "--print-info"))
			param.allowed_logs |= LOG_INFO;
		else if (is_option(av[i], NULL, "--no-print-info"))
			param.allowed_logs &= ~LOG_INFO;
		else if (is_option(av[i], NULL, "--print-action"))
			param.allowed_logs |= LOG_ACTION;
		else if (is_option(av[i], NULL, "--no-print-action"))
			param.allowed_logs &= ~LOG_ACTION;
		else if (is_option(av[i], NULL, "--print-received"))
			param.allowed_logs |= LOG_RECEIVE;
		else if (is_option(av[i], NULL, "--no-print-received"))
			param.allowed_logs &= ~LOG_RECEIVE;
		else if (is_option(av[i], NULL, "--print-death"))
			param.allowed_logs |= LOG_PLAYERDEATH;
		else if (is_option(av[i], NULL, "--no-print-death"))
			param.allowed_logs &= ~LOG_PLAYERDEATH;
		else if (is_option(av[i], NULL, "--print-egg-death"))
			param.allowed_logs |= LOG_EGGDEATH;
		else if (is_option(av[i], NULL, "--no-print-egg-death"))
			param.allowed_logs &= ~LOG_EGGDEATH;
		else if (is_option(av[i], NULL, "--print-connexion"))
			param.allowed_logs |= LOG_CONNEXION;
		else if (is_option(av[i], NULL, "--no-print-connexion"))
			param.allowed_logs &= ~LOG_CONNEXION;
		else if (is_option(av[i], NULL, "--print-error"))
			param.allowed_logs |= LOG_ERROR;
		else if (is_option(av[i], NULL, "--no-print-error"))
			param.allowed_logs &= ~LOG_ERROR;
		else if (is_option(av[i], NULL, "--print-colors"))
			param.flags |= FLAG_COLOR;
		else if (is_option(av[i], NULL, "--no-print-colors"))
			param.flags &= ~FLAG_COLOR;
		else if (is_option(av[i], NULL, "--print-sent"))
			param.allowed_logs |= LOG_SEND;
		else if (is_option(av[i], NULL, "--no-print-sent"))
			param.allowed_logs &= ~LOG_SEND;
		else if (is_option(av[i], "-P", "--pedantic"))
			param.flags |= FLAG_PEDANTIC;
		else if (i + 1 >= ac) //TODO: Improve option parsing
		{
			printf(ERROR_INV_OPT_END, av[i]);
			usage(1);
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
		else if (is_option(av[i], "-l", "--log-replay"))
		{
			int fd = 0;
			if (param.replay_fd  == 0)
				fd = open(av[++i], O_CREAT | O_WRONLY, S_IRWXU | S_IRGRP);
			else
			{
				fprintf(stderr, ERROR_INV_OPT_TOO_MANY_REPLAYS);
				usage(1);
			}
			if (fd >= 0)
				param.replay_fd = fd;
			else
			{
				fprintf(stderr, ERROR_INV_PARAM_FILE, av[i]);
				perror("");
				usage(1);
			}

		}
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
			{
				fprintf(stderr, ERROR_INV_PARAM_GEN, av[i]);
				usage(1);
			}
		}
		else
		{
			printf(ERROR_INV_OPT_UNKNOWN,av[i]);
			usage(1);
		}
	}
	if (!is_input_complete(param))
		usage(1);
	return (param);
}
