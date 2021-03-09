/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:01:58 by jayache           #+#    #+#             */
/*   Updated: 2018/11/08 22:14:34 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t x;

	x = 0;
	while (x < n)
	{
		if (((unsigned char*)s)[x++] == (unsigned char)c)
		{
			return (((void*)s) + x - 1);
		}
	}
	return (NULL);
}
