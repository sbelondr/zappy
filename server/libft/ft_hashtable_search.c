/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable_search.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 09:56:04 by jayache           #+#    #+#             */
/*   Updated: 2019/12/08 10:00:19 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** RETURN ELEMENT AT INDEX N, OR TABLE DEFAULT IF NOTHING IS FOUND
*/

void	*ft_hashtable_search(t_hashtable *table, const char *index)
{
	size_t	key;
	t_list	*current;

	key = ft_hashtable_hash(index) % table->size;
	current = table->content[key];
	while (current)
	{
		if (!ft_strcmp(((t_hashnode*)current->content)->key, index))
			return (((t_hashnode*)current->content)->content);
		current = current->next;
	}
	return (table->def);
}
