/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:01:48 by jayache           #+#    #+#             */
/*   Updated: 2018/12/09 15:40:31 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include <string.h>
#	include "libft.h"
#	include <stdlib.h>

char	*ft_strndup(const char *s1, int n)
{
	char	*s2;
	int		x;

	x = 0;
	s2 = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	while (s1[x] && x < n)
	{
		s2[x] = s1[x];
		++x;
	}
	s2[x] = '\0';
	return (s2);
}
