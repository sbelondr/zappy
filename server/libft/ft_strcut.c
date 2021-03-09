/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 18:23:12 by jayache           #+#    #+#             */
/*   Updated: 2019/08/18 18:23:19 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut(char *cut, int begin, int end)
{
	char	*result;
	int		i;
	int		x;

	result = ft_strnew(ft_strlen(cut));
	x = 0;
	i = 0;
	while (cut[i])
	{
		if (i < begin || i > end)
			result[x++] = cut[i];
		++i;
	}
	return (result);
}
