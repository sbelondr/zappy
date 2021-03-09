/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:58:11 by jayache           #+#    #+#             */
/*   Updated: 2018/12/22 15:58:05 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FRONT PADDING
*/

int	paddingspace(t_arg arg, t_buffer *buf)
{
	int blank;
	int zeros;

	blank = calc_blank_space(arg);
	if (ft_strchr(arg.flags, '0'))
	{
		zeros = ft_strlen(arg.str) - (is_signed(arg));
		if (arg.precision > zeros)
		{
			zeros = arg.precision - zeros;
			blank -= zeros;
		}
		else
			blank = 0;
	}
	else if (!ft_strchr(arg.flags, '0') && arg.precision != -1)
	{
		zeros = arg.precision - (ft_strlen(arg.str) - (arg.str[0] == '-'));
		if (zeros > 0)
			blank -= zeros;
	}
	zeros = 0;
	while (zeros < blank && !ft_strchr(arg.flags, '-'))
		zeros += printf_putchar(buf, ' ');
	return (zeros < 0 || ft_strchr(arg.flags, '-') ? 0 : zeros);
}

int	paddingzeros(t_arg arg, t_buffer *buf)
{
	int blank;
	int zeros;
	int i;

	i = 0;
	blank = (ft_strlen(arg.str) + (ft_strchr(arg.flags, ' ') != NULL) +
	(sign(arg, NULL, arg.str))) + hashflag(arg, NULL, arg.str);
	blank = arg.minimum - blank;
	zeros = 0;
	if (ft_strchr(arg.flags, '0') && !ft_strchr(arg.flags, '-'))
	{
		zeros = ft_strlen(arg.str) - (is_signed(arg));
		if (arg.precision > zeros)
			zeros = arg.precision - zeros;
		else
			zeros = blank;
	}
	else if ((!ft_strchr(arg.flags, '0') || ft_strchr(arg.flags, '-')) &&
	arg.precision != -1)
		zeros = arg.precision - (ft_strlen(arg.str) - (arg.str[0] == '-'));
	while (i < zeros)
		i += printf_putchar(buf, '0');
	return (i < 0 ? 0 : i);
}

int	reverse_padding(t_arg arg, t_buffer *buf, int size)
{
	int i;

	i = 0;
	while (i + size < arg.minimum && ft_strchr(arg.flags, '-'))
	{
		printf_putchar(buf, ' ');
		i++;
	}
	return (i);
}

int	sign(t_arg arg, t_buffer *buf, char *str)
{
	if (str[0] != '-' && ft_strchr(arg.flags, '+'))
	{
		if (buf == NULL)
			return (1);
		printf_putchar(buf, '+');
		return (1);
	}
	return (0);
}

int	hashflag(t_arg arg, t_buffer *buf, char *str)
{
	if (arg.type == 'o' && ft_strchr(arg.flags, '#'))
	{
		if (buf)
			printf_putchar(buf, '0');
		return (1);
	}
	if ((arg.type == 'x' || arg.type == 'X' || arg.type == 'p') &&
	ft_strchr(arg.flags, '#') && (ft_atoi(str) || arg.type == 'p'))
	{
		if (buf != NULL)
		{
			printf_putchar(buf, '0');
			printf_putchar(buf, arg.type == 'X' ? 'X' : 'x');
		}
		return (2);
	}
	return (0);
}
