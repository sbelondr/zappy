/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_projection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 23:42:09 by jayache           #+#    #+#             */
/*   Updated: 2019/08/31 15:21:03 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_matrix	ft_matrix_projection(float ratio, int near, int far, int fov)
{
	t_matrix	matrix;
	float		right;
	float		left;
	float		top;
	float		bottom;

	top = tanf(fov / 2);
	right = top * ratio;
	left = -right;
	bottom = -top;
	matrix = ft_matrix(4, 4);
	matrix.matrix[0][0] = (near * 2) / (right - left);
	matrix.matrix[0][2] = (right + left) / (right - left);
	matrix.matrix[1][1] = (near * 2) / (top - bottom);
	matrix.matrix[1][2] = (top + bottom) / (top - bottom);
	matrix.matrix[2][2] = -(far + near) / (far - near);
	matrix.matrix[2][3] = -(far * 2 * near) / (far - near);
	matrix.matrix[3][2] = -1;
	return (matrix);
}
