/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_print_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:18:00 by jayache           #+#    #+#             */
/*   Updated: 2018/12/08 16:46:43 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_arg_nbr(t_arg arg, t_buffer *buf, char *str)
{
	int size;
	int i;

	i = 0;
	size = (str[0] == '-');
	if (ft_strchr(arg.flags, ' ') && !ft_strchr(arg.flags, '+') &&
	arg.str[0] != '-')
	{
		printf_putchar(buf, ' ');
		++i;
	}
	i += sign(arg, buf, arg.str);
	arg.str[0] == '-' ? printf_putchar(buf, '-') : 0;
	i += paddingzeros(arg, buf);
	while (str[size])
		printf_putchar(buf, str[size++]);
	return (size + i);
	arg.str[0] = 0;
}

int	print_arg_oct(t_arg arg, t_buffer *buf, char *str)
{
	int i;
	int size;

	size = 0;
	i = 0;
	if (str[0] == '0' && arg.precision == 0 && !arg.minimum)
		return (0);
	else if (str[0] == '0' && arg.precision == 0)
	{
		printf_putchar(buf, ' ');
		return (1);
	}
	size += paddingzeros(arg, buf);
	while (str[i])
		printf_putchar(buf, str[i++]);
	return (i + size);
}

int	print_arg_hexa(t_arg arg, t_buffer *buf, char *str)
{
	int i;
	int c;

	i = 0;
	if (str[0] == '0' && arg.precision == 0 && !arg.minimum)
		return (0);
	else if (str[0] == '0' && arg.precision == 0)
	{
		printf_putchar(buf, ' ');
		return (1);
	}
	c = paddingzeros(arg, buf);
	while (str[i])
		printf_putchar(buf, str[i++]);
	return (i + c);
}
