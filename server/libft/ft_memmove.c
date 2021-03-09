/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:39:00 by jayache           #+#    #+#             */
/*   Updated: 2019/08/18 18:22:12 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

static void		*copyfront(void *dst, const void *src, size_t len)
{
	size_t x;

	x = 0;
	while (x < len)
	{
		((unsigned char*)dst)[x] = ((unsigned char*)src)[x];
		++x;
	}
	return (dst);
}

static void		*copyback(void *dst, const void *src, size_t len)
{
	size_t x;

	x = len - 1;
	while (x + 1)
	{
		((unsigned char*)dst)[x] = ((unsigned char*)src)[x];
		--x;
	}
	return (dst);
}

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!len)
		return (dst);
	if (dst < src)
		return (copyfront(dst, src, len));
	else
		return (copyback(dst, src, len));
}
