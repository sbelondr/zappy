/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 09:59:11 by jayache           #+#    #+#             */
/*   Updated: 2019/12/08 10:13:26 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_hashtable	*ft_hashtable_new(size_t size, void *def)
{
	t_hashtable *table;

	table = (t_hashtable*)malloc(sizeof(t_hashtable));
	table->size = size;
	table->content = (t_list**)ft_memalloc(size * sizeof(t_list*));
	table->def = def;
	return (table);
}
