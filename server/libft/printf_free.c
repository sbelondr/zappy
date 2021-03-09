/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 10:38:07 by jayache           #+#    #+#             */
/*   Updated: 2018/12/11 10:38:24 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	free_buffer(t_buffer *buf)
{
	t_fd *fd;

	fd = &(buf->fd);
	if (fd->fd)
	{
		free(fd->fd);
		fd->fd = NULL;
	}
	if (fd->moment)
	{
		free(fd->moment);
		fd->moment = NULL;
	}
	free(buf->buffer);
}

void	free_arg(t_arg *arg)
{
	if (arg->str)
	{
		free(arg->str);
		arg->str = NULL;
	}
	if (arg->flags)
	{
		free(arg->flags);
		arg->flags = NULL;
	}
	if (arg->conversion)
	{
		free(arg->conversion);
		arg->conversion = NULL;
	}
}
