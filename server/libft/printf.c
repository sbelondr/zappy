/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:10:20 by jayache           #+#    #+#             */
/*   Updated: 2018/12/22 16:09:23 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** INIT A TAB
*/

extern void	(**tab_init(void))(t_arg arg, t_buffer *buff, va_list *valist)
{
	void	(**parray)(t_arg, t_buffer*, va_list*);
	int		i;

	i = 0;
	if (!(parray = ft_memalloc(255 * sizeof(*parray))))
		return (NULL);
	while (i < 255)
		(parray)[i++] = &invalid_arg;
	(parray)['s'] = &ft_printf_putstr;
	(parray)['d'] = &ft_printf_putnbr;
	(parray)['c'] = &ft_printf_putchar;
	(parray)['i'] = &ft_printf_putnbr;
	(parray)['o'] = &ft_printf_putoct;
	(parray)['u'] = &ft_printf_putuns;
	(parray)['x'] = &ft_printf_puthexa;
	(parray)['X'] = &ft_printf_puthexa;
	(parray)['%'] = &ft_printf_putpercent;
	(parray)['U'] = &ft_printf_putlonguns;
	(parray)['p'] = &ft_printf_putptr;
	(parray)['f'] = &ft_printf_putfloat;
	(parray)['K'] = &ft_printf_putcolor;
	(parray)['F'] = &ft_printf_putfd;
	(parray)['b'] = &ft_printf_putbinary;
	return (parray);
}

/*
** PRINTS NEXT ARG
*/

extern int	printarg(t_arg arg, t_buffer *buf, va_list *ap)
{
	static void	(**parray[255])(t_arg, t_buffer*, va_list*);

	if (*parray == NULL)
	{
		if (!(parray[0] = tab_init()))
			return (-1);
	}
	(*parray)[arg.type](arg, buf, ap);
	return (1);
}

int			ft_printf(const char *format, ...)
{
	int			x;
	va_list		ap;
	t_arg		arg;
	t_buffer	buf;
	int			tx;

	buf = init_buffer();
	tx = 0;
	va_start(ap, format);
	x = ft_printf_printstr(&buf, format, 0);
	while (format[x + tx])
	{
		arg = parsearg(format, x + tx);
		if (printarg(arg, &buf, &ap) == -1)
			return (-1);
		x += ft_printf_printstr(&buf, format, x + tx + arg.size);
		tx += arg.size;
	}
	printf_write(buf);
	va_end(ap);
	free_buffer(&buf);
	return (buf.bufx);
}
