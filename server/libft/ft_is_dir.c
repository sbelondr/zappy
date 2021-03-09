/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 17:58:44 by jayache           #+#    #+#             */
/*   Updated: 2019/08/09 15:17:06 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_dir(char *name)
{
	struct stat	buf;

	lstat(name, &buf);
	if (errno)
	{
		errno = 0;
		return (0);
	}
	return ((buf.st_mode & S_IFDIR) == S_IFDIR);
}
