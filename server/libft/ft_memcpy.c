/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:06:22 by jayache           #+#    #+#             */
/*   Updated: 2018/11/07 17:50:11 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	while (n)
	{
		((unsigned char*)dst)[n - 1] = ((unsigned char*)src)[n - 1];
		--n;
	}
	return (dst);
}
