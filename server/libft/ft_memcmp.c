/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:16:44 by jayache           #+#    #+#             */
/*   Updated: 2018/11/10 16:22:41 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t x;

	x = 0;
	while (x < n)
	{
		if (((unsigned char*)s1)[x] != ((unsigned char*)s2)[x])
		{
			return (((unsigned char*)s1)[x] - ((unsigned char*)s2)[x]);
		}
		x++;
	}
	return (0);
}
