/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:16:44 by jayache           #+#    #+#             */
/*   Updated: 2018/11/10 12:32:26 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include <string.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t x;

	x = 0;
	if (!s1 && !s2)
		return (0);
	if ((!s1 && s2) || (s1 && !s2))
		return (((unsigned char*)s1)[x] - ((unsigned char*)s2)[x]);
	while (s1[x] && s2[x])
	{
		if (((unsigned char*)s1)[x] != ((unsigned char*)s2)[x])
		{
			return (((unsigned char*)s1)[x] - ((unsigned char*)s2)[x]);
		}
		x++;
	}
	return (((unsigned char*)s1)[x] - ((unsigned char*)s2)[x]);
}
