/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_essentials.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:32:41 by jayache           #+#    #+#             */
/*   Updated: 2019/09/14 12:05:09 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		printf_putchar(t_buffer *buf, char c)
{
	char *tmp;

	if (buf->bufx > buf->size - 10)
	{
		tmp = buf->buffer;
		if (!(buf->buffer = ft_strnew(buf->size + 500)))
			ft_error(ERROR_MALLOC);
		ft_strcpy(buf->buffer, tmp);
		buf->size += 500;
		free(tmp);
	}
	buf->buffer[buf->bufx] = c;
	buf->bufx += 1;
	return (1);
}

int		printf_putuchar(t_buffer *buf, int c)
{
	char *tmp;

	if (buf->bufx > buf->size - 10)
	{
		tmp = buf->buffer;
		if (!(buf->buffer = ft_strnew(buf->size + 500)))
			ft_error(ERROR_MALLOC);
		ft_strcpy(buf->buffer, tmp);
		buf->size += 500;
		free(tmp);
	}
	buf->buffer[buf->bufx] = c;
	buf->bufx += 4;
	return (1);
}

int		calc_blank_space(t_arg arg)
{
	return (arg.minimum - ((ft_strlen(arg.str) + (ft_strchr(arg.flags, ' ') !=
	NULL) + (sign(arg, NULL, arg.str))) + hashflag(arg, NULL, arg.str)));
}

void	ptolower(char *c)
{
	*c = ft_tolower(*c);
}

int		is_signed(t_arg arg)
{
	return (sign(arg, NULL, arg.str) || arg.str[0] == '-');
}
