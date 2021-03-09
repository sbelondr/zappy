/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_translation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 22:39:26 by jayache           #+#    #+#             */
/*   Updated: 2019/08/29 23:01:50 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_matrix	ft_matrix_translation(t_vector3 translation)
{
	t_matrix matrix;

	matrix = ft_matrix_identity();
	matrix.matrix[0][3] = translation.x;
	matrix.matrix[1][3] = translation.y;
	matrix.matrix[2][3] = translation.z;
	return (matrix);
}
