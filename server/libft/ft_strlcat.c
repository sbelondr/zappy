/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:14:23 by jayache           #+#    #+#             */
/*   Updated: 2018/11/09 11:09:38 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t size)
{
	int		x;
	int		j;
	size_t	c;
	size_t	ls1;

	if (!size)
		return (ft_strlen(s2));
	ls1 = ft_strlen(s1);
	j = 0;
	x = 0;
	c = 0;
	while (s1[x] && c < size)
	{
		++x;
		++c;
	}
	while (s2[j] && c < size - 1)
	{
		s1[x + j] = s2[j];
		++j;
		++c;
	}
	if (c < size)
		s1[x + j] = '\0';
	return ((ls1 > size ? size + ft_strlen(s2) : ls1 + ft_strlen(s2)));
}
