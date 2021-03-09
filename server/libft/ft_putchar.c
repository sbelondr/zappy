/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:57:20 by jayache           #+#    #+#             */
/*   Updated: 2018/11/28 10:39:45 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

int	ft_putchar(unsigned int c)
{
	if (c <= 255)
		return (write(1, &c, 1));
	else if (c <= 65535)
		return (write(1, &c, 2));
	else if (c <= 16777215)
		return (write(1, &c, 3));
	else
		return (write(1, &c, 4));
}
