/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 15:21:12 by jayache           #+#    #+#             */
/*   Updated: 2019/08/18 18:16:27 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_buffer	init_buffer(void)
{
	t_buffer	buf;
	t_fd		fd;

	fd.size = 0;
	fd.moment = ft_memalloc(1);
	fd.fd = ft_memalloc(1);
	buf.size = 1000;
	buf.buffer = ft_strnew(buf.size);
	buf.bufx = 0;
	buf.fd = fd;
	return (buf);
}

void		printf_write(t_buffer buf)
{
	int		i;
	int		x;
	t_fd	fds;
	int		fd;
	int		to_write;

	fds = buf.fd;
	x = 0;
	i = 0;
	fd = 1;
	while (i < buf.bufx)
	{
		to_write = 1;
		if (x < fds.size && fds.moment[x] == i)
			fd = fds.fd[x++];
		if (x < fds.size)
			to_write = fds.moment[x] - i;
		if (!write(fd, buf.buffer + i, to_write))
			return ;
		++i;
	}
}
