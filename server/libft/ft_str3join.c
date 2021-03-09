/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str3join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:27:45 by jayache           #+#    #+#             */
/*   Updated: 2019/08/12 16:37:05 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str3join(const char *a, const char *b, const char *c)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin(a, b);
	if (c && temp)
	{
		result = ft_strjoin(temp, c);
		free(temp);
	}
	else
		result = temp;
	return (result);
}
