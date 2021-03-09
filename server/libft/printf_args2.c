/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:48:06 by jayache           #+#    #+#             */
/*   Updated: 2019/08/18 18:20:30 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** PRINTS A %
*/

void		ft_printf_putpercent(t_arg arg, t_buffer *buf, va_list *ap)
{
	long	i;

	arg.str = ft_strnew(2);
	arg.str[0] = '%';
	arg.str[1] = '\0';
	i = paddingspace(arg, buf);
	printf_putchar(buf, '%');
	i += reverse_padding(arg, buf, i + 1);
	free_arg(&arg);
	if (ap)
		ap = NULL;
}

/*
** PRINTS A UNSIGNED OCTAL
*/

void		ft_printf_putoct(t_arg arg, t_buffer *buf, va_list *ap)
{
	uintmax_t	i;
	int			size;

	i = take_unsigned_arg(arg, ap);
	arg.str = ft_itoa_base(i, 8);
	i = paddingspace(arg, buf);
	i += hashflag(arg, buf, arg.str);
	size = print_arg_oct(arg, buf, arg.str);
	i += reverse_padding(arg, buf, i + size);
	free_arg(&arg);
}

void		ft_printf_putuns(t_arg arg, t_buffer *buf, va_list *ap)
{
	uintmax_t	i;
	int			s;

	i = take_unsigned_arg(arg, ap);
	arg.str = ft_itoa_base(i, 10);
	i = paddingspace(arg, buf);
	i += paddingzeros(arg, buf);
	s = 0;
	while (arg.str[s])
		printf_putchar(buf, arg.str[s++]);
	i += reverse_padding(arg, buf, i + ft_strlen(arg.str));
	free_arg(&arg);
}

void		ft_printf_puthexa(t_arg arg, t_buffer *buf, va_list *ap)
{
	uintmax_t	i;
	int			size;

	i = take_unsigned_arg(arg, ap);
	arg.str = ft_itoa_base(i, 16);
	i = 0;
	if (ft_strchr(arg.flags, '0'))
		i = hashflag(arg, buf, arg.str);
	i += paddingspace(arg, buf);
	if (!ft_strchr(arg.flags, '0'))
		i += hashflag(arg, buf, arg.str);
	if (arg.type == 'x' || arg.type == 'p')
		ft_striter(arg.str, &ptolower);
	size = print_arg_hexa(arg, buf, arg.str);
	i += reverse_padding(arg, buf, i + size);
	free_arg(&arg);
}
