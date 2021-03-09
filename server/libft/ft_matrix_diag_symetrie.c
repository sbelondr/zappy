/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_diag_symetrie.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 23:25:58 by jayache           #+#    #+#             */
/*   Updated: 2019/08/29 23:35:22 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_matrix	ft_matrix_diag_symetrie(t_matrix matrix)
{
	t_matrix	m;
	int			x;
	int			y;

	m = ft_matrix(matrix.height, matrix.width);
	y = 0;
	while (y < matrix.height)
	{
		x = 0;
		while (x < matrix.width)
		{
			m.matrix[x][y] = matrix.matrix[y][x];
			++x;
		}
		++y;
	}
	return (m);
}
