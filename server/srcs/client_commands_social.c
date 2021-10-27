/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_commands_social.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:15:43 by selver            #+#    #+#             */
/*   Updated: 2021/10/27 16:39:38 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char	*player_fork(t_srv *srv,t_world_state *world, t_client *player)
{
	t_egg	egg;
	t_list	*current;
	int		maxid;

	maxid = 0;
	egg.team_name = ft_strdup(player->team_name);
	egg.p_x = player->p_x;
	egg.p_y = player->p_y;
	egg.father_id = player->id;
	current = world->egg_list;	
	while (current)
	{
		if (((t_egg*)current->content)->id > maxid)
			maxid = ((t_egg*)current->content)->id;
		current = current->next;
	}
	egg.id = maxid + 1;
	ft_lst_append(&world->egg_list, ft_lstnew(&egg, sizeof(t_egg)));
	add_egg_to_team(world, player->team_name, egg.id);
	printf("[%d] a pondu un oeuf avec l'ID %d !", player->id, egg.id);
	send_to_all_moniteur(srv, moniteur_enw(&egg));
	return (ft_strdup("OK"));
}
