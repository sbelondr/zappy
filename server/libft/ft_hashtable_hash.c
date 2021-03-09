/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashtable_hash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 09:58:19 by jayache           #+#    #+#             */
/*   Updated: 2019/12/08 10:00:47 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** GENERATE A KEY FROM A STRING
*/

size_t	ft_hashtable_hash(const char *key)
{
	size_t	asciisum;
	int		i;

	i = 0;
	asciisum = 0;
	while (key[i])
	{
		asciisum += (key[i] * i);
		++i;
	}
	return (asciisum %= 599);
}
