/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 10:28:34 by jayache           #+#    #+#             */
/*   Updated: 2019/12/09 10:30:05 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_hashtable_size(t_hashtable *table)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (i < table->size)
	{
		size += ft_lst_size(table->content[i]);
		++i;
	}
	return (size);
}
