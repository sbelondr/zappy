/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:01:48 by jayache           #+#    #+#             */
/*   Updated: 2019/09/14 12:07:22 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include <string.h>
#	include "libft.h"
#	include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		x;

	x = 0;
	s2 = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s2)
	{
		return (NULL);
	}
	while (s1[x])
	{
		s2[x] = s1[x];
		++x;
	}
	s2[x] = '\0';
	return (s2);
}
