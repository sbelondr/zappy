/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 10:23:21 by jayache           #+#    #+#             */
/*   Updated: 2019/12/08 10:33:18 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "ft_printf.h"

/*
** CALLED IN CASE OF BAD ARG
*/

void	invalid_arg(t_arg arg, t_buffer *buf, va_list *ap)
{
	return ;
	printf_putchar(buf, '0');
	if (ap && arg.flags)
		arg.flags = NULL;
}

/*
** PRINTS AN INTEGER
*/

void	ft_printf_putnbr(t_arg arg, t_buffer *buf, va_list *ap)
{
	intmax_t	i;
	int			size;

	i = take_int_arg(arg, ap);
	arg.str = ft_itoa(i);
	i = 0;
	if (arg.precision == 0 && arg.str[0] == '0')
		arg.str[0] = '\0';
	i = paddingspace(arg, buf);
	size = print_arg_nbr(arg, buf, arg.str);
	i += reverse_padding(arg, buf, i + size);
	free_arg(&arg);
}

/*
** PRINTS A STRING
*/

void	ft_printf_putstr(t_arg arg, t_buffer *buf, va_list *ap)
{
	int		x;
	int		i;

	arg.str = (char*)va_arg(*ap, char*);
	if (!arg.str)
		arg.str = "(null)";
	i = strpadding(arg, buf, ft_strlen(arg.str));
	x = 0;
	while (arg.str[x] && (x < arg.precision || arg.precision == -1))
	{
		printf_putchar(buf, arg.str[x]);
		++x;
	}
	if (arg.precision != -1)
		i += reverse_padding(arg, buf, i + ft_min(ft_strlen(arg.str),
		arg.precision));
	else
		i += reverse_padding(arg, buf, i + ft_strlen(arg.str));
	arg.str = NULL;
	free_arg(&arg);
}

/*
** PRINTS A CHAR
*/

void	ft_printf_putchar(t_arg arg, t_buffer *buf, va_list *ap)
{
	char	c;
	int		x;

	x = 1;
	c = (char)va_arg(*ap, int);
	arg.str = ft_strdup("c\0");
	x = paddingspace(arg, buf);
	printf_putchar(buf, c);
	x += reverse_padding(arg, buf, x + 1);
	free_arg(&arg);
}

/*
** PRINTS FORMAT UNTIL NEXT ARG
*/

int		ft_printf_printstr(t_buffer *buf, const char *str, int x)
{
	int s;

	s = 0;
	while (str[x] != '%' && str[x])
	{
		printf_putchar(buf, str[x]);
		++x;
		++s;
	}
	return (s);
}
