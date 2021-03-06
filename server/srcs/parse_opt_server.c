/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt_server.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:11:09 by sbelondr          #+#    #+#             */
/*   Updated: 2021/03/04 09:45:13 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
-p numero de port
-x largeur du Monde
-y hauteur du Monde
-n nom\_equipe\_1 nom\_\_equipe_2 ...
-c nombre de client autorises au commencement du jeu
-t diviseur de l'unite de temps (plus t est grand, plus le jeu va vite)
*/

t_settings_srv	*ft_parse_arg_srv(char **av)
{
	(void)av;
	// call super jayache function
	
	t_settings_srv	*settings_src;
	char			**team;
	if (!(settings_src = (t_settings_srv*)malloc(sizeof(t_settings_srv) * 1)))
		return (NULL);

	if (!(team = (char**)malloc(sizeof(char*) * 3)))
		return (NULL);
	team[0] = strdup("jayache");
	team[1] = strdup("sbelondr");
	team[2] = 0;
	settings_src->port = 8080;
	settings_src->x = 1000;
	settings_src->y = 1000;
	settings_src->team = team;
	settings_src->max_client = 10;
	settings_src->time = 1;
	return (settings_src);
}
