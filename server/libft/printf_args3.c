/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_args3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 14:54:14 by jayache           #+#    #+#             */
/*   Updated: 2018/12/12 11:31:30 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	TAKE A 'U'
**	PASS IT TO 'u'
**	CONVERTED JUST FOR U
*/

void	ft_printf_putlonguns(t_arg arg, t_buffer *buf, va_list *ap)
{
	uintmax_t	i;
	int			s;

	s = 0;
	i = (unsigned long)va_arg(*ap, long);
	arg.str = ft_itoa_base(i, 10);
	i = paddingspace(arg, buf);
	i += paddingzeros(arg, buf);
	s = 0;
	while (arg.str[s])
		printf_putchar(buf, arg.str[s++]);
	i += reverse_padding(arg, buf, i + ft_strlen(arg.str));
	free_arg(&arg);
}

/*
**	puts-a-ptr
*/

void	ft_printf_putptr(t_arg arg, t_buffer *buf, va_list *ap)
{
	arg = arg_add_flag(arg, "#");
	arg = arg_change_conv(arg, "l");
	ft_printf_puthexa(arg, buf, ap);
}

/*
** The true f in f-
*/

void	ft_printf_putfloat(t_arg arg, t_buffer *buf, va_list *ap)
{
	long double	f;
	int			s;
	int			i;

	s = 0;
	f = take_double_arg(arg, ap);
	if (arg.precision == -1)
		arg.precision = 6;
	arg.str = ft_itoa((intmax_t)(ft_pow(10, arg.precision) * f));
	if (f < 1 && f > 0)
		ft_stradd(&arg.str, '0');
	i = paddingspace(arg, buf);
	i += paddingzeros(arg, buf);
	while (arg.str[s + arg.precision])
		s += printf_putchar(buf, arg.str[s]);
	i += printf_putchar(buf, '.');
	while (arg.str[s])
		s += printf_putchar(buf, arg.str[s]);
	i += reverse_padding(arg, buf, i + ft_strlen(arg.str));
	free_arg(&arg);
}

void	ft_printf_putfd(t_arg arg, t_buffer *buf, va_list *ap)
{
	t_fd	fd;
	int		*moment;
	int		*fds;

	fd = buf->fd;
	moment = ft_memalloc(((fd.size + 1) * sizeof(int) + 1));
	if (!(fds = ft_memalloc((fd.size + 1) * sizeof(int) + 1)) || !moment)
		exit(1);
	ft_memcpy(moment, fd.moment, fd.size + 1);
	ft_memcpy(fds, fd.fd, fd.size + 1);
	free(fd.moment);
	free(fd.fd);
	fd.fd = fds;
	fd.moment = moment;
	fd.moment[fd.size] = buf->bufx;
	fd.fd[fd.size] = va_arg(*ap, int);
	if (write(fd.fd[fd.size], "test", 0) == -1)
		invalid_arg(arg, buf, ap);
	fd.size++;
	buf->fd = fd;
	free_arg(&arg);
}

void	ft_printf_putbinary(t_arg arg, t_buffer *buf, va_list *ap)
{
	uintmax_t	i;
	int			s;

	i = take_unsigned_arg(arg, ap);
	arg.str = ft_itoa_base(i, 2);
	i = paddingspace(arg, buf);
	if (arg.precision == -1)
		i += paddingzeros(arg, buf);
	s = 0;
	while (arg.str[s])
		printf_putchar(buf, arg.str[s++]);
	while (s++ < arg.precision && arg.precision != -1)
		printf_putchar(buf, '0');
	i += reverse_padding(arg, buf, i + ft_strlen(arg.str));
	free_arg(&arg);
}
