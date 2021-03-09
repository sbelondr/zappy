/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable_clean.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 10:01:18 by jayache           #+#    #+#             */
/*   Updated: 2019/12/08 10:02:45 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_hashnode(void *hashnode, size_t size)
{
	t_hashnode	*hn;

	hn = hashnode;
	free(hn->key);
	free(hn->content);
	free(hashnode);
	if (size > 15)
		return ;
}

void		ft_hashtable_clean(t_hashtable *table)
{
	size_t	i;

	i = 0;
	while (i < table->size)
	{
		if (table->content[i])
		{
			ft_lstdel(&(table->content[i]), free_hashnode);
		}
		++i;
	}
	free(table->content);
	free(table);
}
