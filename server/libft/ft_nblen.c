/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nblen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:17:55 by jayache           #+#    #+#             */
/*   Updated: 2018/11/30 15:30:29 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	RETURN THE SIZE OF THE NUMBER
**	OR THE SIZE + 1 IF IT IS NEGATIVE
*/

int	ft_nblen(int nb)
{
	long	snb;
	int		c;

	c = (nb < 0);
	snb = ft_abs(nb);
	if (nb == 0)
		return (1);
	while (snb > 0)
	{
		++c;
		snb /= 10;
	}
	return (c);
}
