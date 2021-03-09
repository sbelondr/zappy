/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:56:30 by jayache           #+#    #+#             */
/*   Updated: 2018/12/10 11:08:26 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** CONVERTS NB IN AN UNSIGNED DIGIT OF SIZE BASE
** MAX BASE (CURRENT) IS 16
** RETURN NULL ON FAILURE
*/

static int	nblen_base(long nb, int base)
{
	int x;

	x = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= base;
		++x;
	}
	return (x);
}

char		*ft_itoa_base(long long nb, int base)
{
	char				*str;
	int					c;
	int					s;
	unsigned long long	nbs;

	nbs = ft_abs(nb);
	s = nblen_base(nbs, base);
	c = 0;
	if (base > 16 || base < 2)
		return (NULL);
	str = ft_strnew(s);
	if (nb == 0)
		str[c++] = '0';
	while (nbs > 0)
	{
		str[s - c - 1] = "0123456789ABCDEF"[ft_abs(nbs % base)];
		nbs /= base;
		++c;
	}
	str[c] = '\0';
	return (str);
}
