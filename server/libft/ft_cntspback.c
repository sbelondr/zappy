/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntspback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:51:47 by jayache           #+#    #+#             */
/*   Updated: 2018/11/18 12:23:17 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

size_t	ft_cntspback(char const *s, char const c)
{
	size_t x;

	x = ft_strlen(s) - 1;
	while (s[x] == c)
		--x;
	return ((ft_strlen(s) - 1) - x);
}
