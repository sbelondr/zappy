/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniteur_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 09:07:00 by selver            #+#    #+#             */
/*   Updated: 2021/10/25 10:02:56 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int asprintf(char **strp, const char *fmt, ...);

//Taille de la carte
char	*moniteur_msz(t_world_state *world)
{
	char	*ret;
	int		error;
	t_param	p;

	p = world->params;
	error = asprintf(&ret, "msz %d %d\n", p.world_width, p.world_height);
	if (error < 0)
		ft_error("Fatal: asprintf a retourné une erreur (" __FILE__ " !!\n");
	return (ret);
}

//Contenu d'une case de la carte 
char	*moniteur_bct(t_world_state *world, int x, int y)
{
	char	*ret;
	int		error;
	int		*quant;

	quant = get_case(world, x, y);	
	error = asprintf(&ret, "bct %d %d %d %d %d %d %d %d %d\n",
			x, y, quant[0], quant[1], quant[2], quant[3], quant[4], quant[5], quant[6]); 
	if (error < 0)
		ft_error("Fatal: asprintf a retourné une erreur (" __FILE__ " !!\n");
	return (ret);
}

//Contenu de la carte
char	*moniteur_mct(t_world_state *world)
{
	char	*ret;
	char	*dup;
	int		error;
	int		c_x;
	int		c_y;

	c_x = 0;
	c_y = 0;
	ret = ft_strdup("");
	while (c_y < world->params.world_height)
	{
		while (c_x < world->params.world_width)
		{
			error = asprintf(&dup, "%s%s", ret, moniteur_bct(world, c_x, c_y));
			if (error < 0)
				ft_error("Fatal: asprintf a retourné une erreur (" __FILE__ " !!\n");
			free(ret);
			ret = dup;
			++c_x;
		}
		++c_y;
		c_x = 0;
	}
	return (ret);
}

//Unité de temps
char	*moniteur_sgt(t_world_state *world)
{
	char	*ret;
	int		error;

	error = asprintf(&ret, "sgt %d\n", world->params.time_delta);
	if (error < 0)
		ft_error("Fatal: asprintf a retourné une erreur (" __FILE__ " !!\n");
	return (ret);
}

//Nom des équipes
char	*moniteur_tna(t_world_state *world)
{
	char	*ret;
	int		error;
	t_list	*current;
	char	*dup;

	ret = ft_strdup("");
	current = world->params.team_list;
	while (current)
	{
		error = asprintf(&dup, "%stna %s\n", ret, ((t_team*)current->content)->team_name);
		if (error < 0)
			ft_error("Fatal: asprintf a retourné une erreur (" __FILE__ " !!\n");
		free(ret);
		ret = dup;
		current = current->next;
	}
	return (ret);
}
