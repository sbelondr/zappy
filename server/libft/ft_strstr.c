/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 23:00:44 by jayache           #+#    #+#             */
/*   Updated: 2018/11/10 16:22:17 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	int x;
	int j;

	x = 0;
	if (needle[0] == '\0')
		return ((char*)haystack);
	while (haystack[x])
	{
		j = 0;
		while (haystack[x + j] == needle[j])
		{
			++j;
			if (!needle[j])
				return ((char*)haystack + x);
		}
		++x;
	}
	return (NULL);
}
