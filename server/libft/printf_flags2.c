/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 11:52:35 by jayache           #+#    #+#             */
/*   Updated: 2018/12/11 14:41:06 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	strpadding(t_arg arg, t_buffer *buf, int size)
{
	int precision;
	int i;

	precision = (arg.precision == -1 ? size + 1 : arg.precision);
	i = 0;
	while (i < arg.minimum - ft_min(size, precision) &&
	!ft_strchr(arg.flags, '-'))
	{
		++i;
		printf_putchar(buf, ' ');
	}
	return (i);
}
