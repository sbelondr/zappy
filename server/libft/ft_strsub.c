/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:31:00 by jayache           #+#    #+#             */
/*   Updated: 2018/11/10 12:36:26 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	x;

	if (!s)
		return (NULL);
	x = 0;
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	while (x < len)
	{
		str[x] = s[start + x];
		++x;
	}
	str[x] = '\0';
	return (str);
}
