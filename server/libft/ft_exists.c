/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 17:58:03 by jayache           #+#    #+#             */
/*   Updated: 2018/12/26 17:58:15 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_exists(char *file)
{
	struct stat	buf;

	lstat(file, &buf);
	if (errno)
	{
		errno = 0;
		return (0);
	}
	return (1);
}
