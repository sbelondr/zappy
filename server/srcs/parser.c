/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:14:09 by selver            #+#    #+#             */
/*   Updated: 2021/03/06 11:12:13 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
t_world_state init_world(t_param params);

void	usage(void)
{
	printf("Usage: ./serveur -p <port> -x <width> -y <height> -n <team> [<team>] [<team>] ... -c <nb> -t <t>\n");
	printf("-p numero de port\n-x largeur du Monden\n-y hauteur du Monde\n-n nom_equipe_1 nom_equipe_2 ...\n");
	printf("-c nombre de client autorises au commencement du jeu\n-t diviseur de l'unite de temps (plus t est grand, plus le jeu va vite)\n");
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
	if (!param.port || !param.world_width || !param.world_height)
	{
		printf("Missing parameters\n");
		usage();
	}
	if (!param.time_delta || !param.allowed_clients_amount)
	{
		printf("Missing parameters\n");
		usage();
	}
	if (!param.team_list || !param.team_list->next)
	{
		printf("Missing parameters\n");
		usage();
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
			param.world_width = get_numeric_parameter(av[++i], 5, 15000);
		}
		else if (!strcmp(av[i], "-y"))
		{
			param.world_height = get_numeric_parameter(av[++i], 5, 15000);
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
	t_world_state st;
	st = init_world(param);
	for (int y = 0; y < st.params.world_height; y++)
	{
		for (int x = 0; x < st.params.world_width; x++)
		{
			printf("[");
			for (int z = 0; z < 7; z++)
			{
				printf("%d ", st.map[y][x][z]);
			}
			printf("]");
		}
		printf("\n");
	}
}
