/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_product.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:39:38 by jayache           #+#    #+#             */
/*   Updated: 2019/08/09 15:16:52 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	productcase(t_matrix a, t_matrix b, int x, int y)
{
	int		t;
	float	result;
	float	aval;
	float	bval;

	result = 0;
	t = 0;
	while (t < b.height)
	{
		aval = y >= a.height || t >= a.width ? 0 : (a.matrix[y])[t];
		bval = x >= b.width || t >= b.height ? 0 : (b.matrix[t])[x];
		result += (aval * bval);
		++t;
	}
	return (result);
}

t_matrix		ft_matrix_product(t_matrix a, t_matrix b)
{
	t_matrix	matrix;
	int			x;
	int			y;

	matrix = ft_matrix(b.width, a.height);
	if (a.width != b.height)
		return (matrix);
	x = 0;
	while (x < matrix.width)
	{
		y = 0;
		while (y < matrix.height)
		{
			(matrix.matrix[y])[x] = productcase(a, b, x, y);
			++y;
		}
		++x;
	}
	return (matrix);
}
