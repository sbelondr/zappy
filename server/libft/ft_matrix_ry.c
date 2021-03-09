/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_ry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 23:15:20 by jayache           #+#    #+#             */
/*   Updated: 2019/08/29 23:21:18 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_matrix	ft_matrix_ry(float angle)
{
	t_matrix	matrix;

	matrix = ft_matrix_identity();
	matrix.matrix[0][0] = cosf(angle);
	matrix.matrix[0][2] = -sinf(angle);
	matrix.matrix[2][1] = sinf(angle);
	matrix.matrix[2][2] = cosf(angle);
	return (matrix);
}
