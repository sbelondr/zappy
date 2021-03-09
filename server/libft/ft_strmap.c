/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:58:11 by jayache           #+#    #+#             */
/*   Updated: 2018/11/10 12:27:42 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		x;
	char	*s2;

	if (!s || !f)
		return (NULL);
	x = 0;
	s2 = ft_strnew(ft_strlen(s));
	if (!s2)
		return (NULL);
	while (s[x])
	{
		s2[x] = f(s[x]);
		++x;
	}
	return (s2);
}
