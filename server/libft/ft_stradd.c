/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 14:55:36 by jayache           #+#    #+#             */
/*   Updated: 2018/12/10 11:05:11 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stradd(char **str, char c)
{
	char	*result;
	char	*sc;

	sc = ft_strnew(1);
	sc[0] = c;
	result = ft_strjoin(sc, *str);
	free(*str);
	free(sc);
	*str = result;
}
