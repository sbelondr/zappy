/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 09:58:26 by jayache           #+#    #+#             */
/*   Updated: 2019/12/08 10:00:08 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** add an element to an existing hashtable
*/

void	ft_hashtable_add(t_hashtable *table, const char *index, void *value)
{
	size_t	key;
	t_list	*current;

	key = ft_hashtable_hash(index) % table->size;
	current = table->content[key];
	while (current)
	{
		if (!ft_strcmp(((t_hashnode*)current->content)->key, index))
		{
			((t_hashnode*)current->content)->content = value;
			return ;
		}
		current = current->next;
	}
	ft_lst_append(&(table->content[key]), ft_lstnew_no_copy(ft_hashnode_new(
					ft_strdup(index), value), sizeof(t_hashnode)));
}
