/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:07:25 by jayache           #+#    #+#             */
/*   Updated: 2018/11/09 13:37:56 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	ft_putnbr(int nb)
{
	long snb;

	snb = ft_abs(nb);
	if (ft_sign(nb) < 0)
		ft_putchar('-');
	if (snb < 10)
		ft_putchar(snb + '0');
	else
	{
		ft_putnbr(snb / 10);
		ft_putnbr(snb % 10);
	}
}
