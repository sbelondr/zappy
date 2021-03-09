/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_arg_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 15:22:03 by jayache           #+#    #+#             */
/*   Updated: 2018/12/11 10:39:39 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*color_table2(t_arg arg)
{
	if (ft_strequ(arg.flags, "red"))
		return ("\e[31m\0");
	else if (ft_strequ(arg.flags, "RED"))
		return ("\e[41m\0");
	else if (ft_strequ(arg.flags, "green"))
		return ("\e[32m\0");
	else if (ft_strequ(arg.flags, "GREEN"))
		return ("\e[42m\0");
	else
		return ("\0");
}

static char	*color_table(t_arg arg)
{
	if (ft_strequ(arg.flags, "yellow"))
		return ("\e[33m\0");
	else if (ft_strequ(arg.flags, "YELLOW"))
		return ("\e[43m\0");
	else if (ft_strequ(arg.flags, "blue"))
		return ("\e[34m\0");
	else if (ft_strequ(arg.flags, "BLUE"))
		return ("\e[44m\0");
	else if (ft_strequ(arg.flags, "pink"))
		return ("\e[35m\0");
	else if (ft_strequ(arg.flags, "PINK"))
		return ("\e[45m\0");
	else if (ft_strequ(arg.flags, "lblue"))
		return ("\e[36m\0");
	else if (ft_strequ(arg.flags, "LBLUE"))
		return ("\e[46m\0");
	else if (ft_strequ(arg.flags, "grey"))
		return ("\e[37m\0");
	else if (ft_strequ(arg.flags, "GREY"))
		return ("\e[47m\0");
	else if (ft_strequ(arg.flags, "black"))
		return ("\e[30m\0");
	else if (ft_strequ(arg.flags, "BLACK"))
		return ("\e[40m\0");
	return (color_table2(arg));
}

void		ft_printf_putcolor(t_arg arg, t_buffer *buf, va_list *ap)
{
	int x;

	x = 0;
	arg.str = color_table(arg);
	while (arg.str[x])
		x += printf_putchar(buf, arg.str[x]);
	arg.str = NULL;
	free_arg(&arg);
	if (!ap)
		ap = NULL;
}
