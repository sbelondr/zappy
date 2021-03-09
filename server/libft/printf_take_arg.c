/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 11:27:35 by jayache           #+#    #+#             */
/*   Updated: 2018/12/11 11:30:16 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "ft_printf.h"

intmax_t	take_int_arg(t_arg arg, va_list *ap)
{
	if (ft_strequ(arg.conversion, "l"))
		return ((intmax_t)va_arg(*ap, long));
	if (ft_strequ(arg.conversion, "z"))
		return ((intmax_t)va_arg(*ap, long));
	if (ft_strequ(arg.conversion, "ll"))
		return ((intmax_t)va_arg(*ap, long long));
	if (ft_strequ(arg.conversion, "h"))
		return ((short)va_arg(*ap, int));
	if (ft_strequ(arg.conversion, "hh"))
		return ((char)va_arg(*ap, int));
	if (ft_strequ(arg.conversion, "j"))
		return (va_arg(*ap, intmax_t));
	return ((intmax_t)va_arg(*ap, int));
}

uintmax_t	take_unsigned_arg(t_arg arg, va_list *ap)
{
	if (ft_strequ(arg.conversion, "l"))
		return ((uintmax_t)va_arg(*ap, unsigned long));
	if (ft_strequ(arg.conversion, "ll"))
		return ((uintmax_t)va_arg(*ap, unsigned long long));
	if (ft_strequ(arg.conversion, "h"))
		return ((unsigned short)va_arg(*ap, unsigned int));
	if (ft_strequ(arg.conversion, "hh"))
		return ((unsigned char)va_arg(*ap, unsigned int));
	if (ft_strequ(arg.conversion, "j"))
		return (va_arg(*ap, uintmax_t));
	if (ft_strequ(arg.conversion, "z"))
		return ((uintmax_t)va_arg(*ap, size_t));
	return ((uintmax_t)va_arg(*ap, unsigned int));
}

long double	take_double_arg(t_arg arg, va_list *ap)
{
	if (ft_strequ(arg.conversion, "L"))
		return (va_arg(*ap, long double));
	return (va_arg(*ap, double));
}
