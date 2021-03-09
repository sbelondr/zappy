/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable_sub.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 09:56:23 by jayache           #+#    #+#             */
/*   Updated: 2019/12/08 09:59:52 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** REMOVE ONE ENTRY
*/

static void	free_f(void *p, size_t size)
{
	t_hashnode	*n;

	n = p;
	free(n->key);
	free(n);
	if (size)
		return ;
}

void		ft_hashtable_sub(t_hashtable *table, const char *index)
{
	size_t		key;
	t_list		*current;
	t_list		*last;
	t_hashnode	*node;

	key = ft_hashtable_hash(index) % table->size;
	current = table->content[key];
	last = NULL;
	while (current)
	{
		node = current->content;
		if (!ft_strcmp(node->key, index))
		{
			if (last)
				last->next = current->next;
			else
				table->content[key] = current->next;
			ft_lstdelone(&current, free_f);
			return ;
		}
		last = current;
		current = current->next;
	}
}
