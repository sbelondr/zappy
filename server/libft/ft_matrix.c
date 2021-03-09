/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:37:48 by jayache           #+#    #+#             */
/*   Updated: 2019/08/29 23:00:48 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_matrix	ft_matrix(int width, int height)
{
	t_matrix	matrix;
	int			x;

	x = 0;
	matrix.height = -1;
	if (!(matrix.matrix = malloc(sizeof(int) * height + 1)))
		return (matrix);
	while (x < height)
	{
		if (!(matrix.matrix[x] = malloc(sizeof(int) * width + 1)))
			return (matrix);
		ft_bzero(matrix.matrix[x], width * sizeof(int));
		++x;
	}
	matrix.height = height;
	matrix.width = width;
	return (matrix);
}
