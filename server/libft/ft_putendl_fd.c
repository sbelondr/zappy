/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:05:36 by jayache           #+#    #+#             */
/*   Updated: 2018/11/08 15:14:47 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

int	ft_putendl_fd(char const *s, int fd)
{
	return (ft_putstr_fd(s, fd) + write(fd, "\n", 1));
}