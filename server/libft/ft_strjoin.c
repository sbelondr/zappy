/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:37:49 by jayache           #+#    #+#             */
/*   Updated: 2018/11/28 10:49:01 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		x;
	int		a;

	a = 0;
	x = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[a])
	{
		str[x] = s1[a];
		++x;
		++a;
	}
	a = 0;
	while (s2[a])
	{
		str[x] = s2[a];
		++x;
		++a;
	}
	str[x] = '\0';
	return (str);
}
