/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 09:58:41 by jayache           #+#    #+#             */
/*   Updated: 2019/12/08 10:01:05 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_hashnode(void *hashnode, size_t size)
{
	t_hashnode	*hn;

	hn = hashnode;
	free(hn->key);
	free(hashnode);
	if (size > 15)
		return ;
}

void		ft_hashtable_free(t_hashtable *table)
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
