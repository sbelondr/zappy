/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   egg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 10:56:24 by jayache           #+#    #+#             */
/*   Updated: 2022/03/04 17:54:18 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

//something

t_egg	*new_egg(t_world_state *w, char const *team_name, t_vector2 pos, int parent_id)
{
	t_egg	*ret;
	t_list	*current;
	int		maxid;

	maxid = -1;
	ret = (t_egg*)malloc(sizeof(t_egg));
	ret->team_name = ft_strdup(team_name);
	ret->p_x = pos.x;
	ret->p_y = pos.y;
	ret->father_id = parent_id;
	ret->food = 10;
	ret->maturity = 600;
	current = w->egg_list;
	while (current)
	{
		if (((t_egg *)current->content)->id > maxid)
			maxid = ((t_egg *)current->content)->id;
		current = current->next;
	}
	ret->id = maxid + 1;
	return (ret);
}

void	rotten_egg(t_srv *srv, t_egg *egg)
{
	t_team *team;

	int	mcmp(t_egg *a, t_egg *b) { 	return a->id - b->id; }
	void	mdel(t_egg *a) { (void)a; }
	send_to_all_moniteur(srv, moniteur_edi(egg));
	ft_lstdelbyval(&srv->world->egg_list, egg, mcmp, mdel);
	team = get_team_by_name(srv->world, egg->team_name);
	ft_lstdelbyval(&team->team_eggs, egg, mcmp, mdel);
	free(egg->team_name);
	free(egg);
	if (can_print(srv->param, LOG_EGGDEATH))
	{
		cyan();
		printf("%ld: An egg died!\n", srv->frame_nbr);
		reset();
	}
}
