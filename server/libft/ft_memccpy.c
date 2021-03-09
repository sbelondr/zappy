/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:19:21 by jayache           #+#    #+#             */
/*   Updated: 2018/11/08 22:14:42 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t x;

	x = 0;
	while (x < n)
	{
		((unsigned char*)dst)[x] = ((unsigned char*)src)[x];
		if (((unsigned char*)src)[x] == (unsigned char)c)
			return (dst + x + 1);
		++x;
	}
	return (NULL);
}
