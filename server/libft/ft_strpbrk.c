/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:46:02 by jayache           #+#    #+#             */
/*   Updated: 2018/12/01 16:11:26 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strpbrk(const char *s, const char *charset)
{
	unsigned int	a;
	char			*best;
	char			*tmp;

	best = NULL;
	a = 0;
	while (a < ft_strlen(charset))
	{
		tmp = ft_strchr(s, charset[a]);
		if (best - tmp > 0 || best == NULL)
			best = tmp;
		++a;
	}
	return (best - s);
}
