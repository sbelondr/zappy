/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:14:21 by jayache           #+#    #+#             */
/*   Updated: 2018/11/10 12:37:23 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

static int		wordcount(char const *s, char c)
{
	int x;
	int count;
	int inword;

	inword = 0;
	count = 0;
	x = 0;
	while (s[x])
	{
		while (s[x] && s[x] != c)
		{
			++x;
			if (!inword)
			{
				inword = 1;
				count++;
			}
		}
		inword = 0;
		while (s[x] && s[x] == c)
			++x;
	}
	return (count);
}

static int		nextword(char const *s, char c, int pos)
{
	while (s[pos])
	{
		if (s[pos] != c)
			return (pos);
		++pos;
	}
	return (0);
}

static int		sizenextword(char const *s, char c, int pos)
{
	int size;

	size = 0;
	while (s[pos])
	{
		while (s[pos] != c && s[pos])
		{
			++size;
			++pos;
		}
		if (size)
			return (size);
		++pos;
	}
	return (0);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		x;
	int		pos;

	if (!s)
		return (NULL);
	pos = 0;
	x = 0;
	str = (char**)malloc(sizeof(char*) * (wordcount(s, c) + 1));
	if (!str)
		return (NULL);
	while (x < wordcount(s, c))
	{
		str[x] = ft_strsub(s, nextword(s, c, pos),
		(size_t)sizenextword(s, c, pos));
		pos = nextword(s, c, pos) + sizenextword(s, c, pos);
		++x;
	}
	str[x] = NULL;
	return (str);
}
