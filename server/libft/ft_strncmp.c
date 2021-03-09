/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:16:44 by jayache           #+#    #+#             */
/*   Updated: 2018/11/10 16:21:33 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t x;

	x = 0;
	if (!n)
		return (0);
	while (x < n && s1[x] && s2[x])
	{
		if (((unsigned char*)s1)[x] != ((unsigned char*)s2)[x])
		{
			return (((unsigned char*)s1)[x] - ((unsigned char*)s2)[x]);
		}
		x++;
	}
	if ((s1 || s2) && x < n)
		return (((unsigned char*)s1)[x] - ((unsigned char*)s2)[x]);
	return (0);
}
