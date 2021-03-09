/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cnt_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 14:13:21 by jayache           #+#    #+#             */
/*   Updated: 2019/08/09 15:17:29 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_cnt_type(char **files, int size, int type)
{
	struct stat buf;
	int			cnt;

	cnt = 0;
	while (size)
	{
		size--;
		lstat(files[size], &buf);
		if (errno == 0 && (buf.st_mode & type) == (unsigned int)type)
			cnt++;
	}
	return (cnt);
}
