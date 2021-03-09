/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_identity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 22:23:26 by jayache           #+#    #+#             */
/*   Updated: 2019/08/29 23:05:58 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_matrix	ft_matrix_identity(void)
{
	t_matrix	matrix;

	matrix = ft_matrix(4, 4);
	matrix.matrix[0][0] = 1;
	matrix.matrix[1][1] = 1;
	matrix.matrix[2][2] = 1;
	matrix.matrix[3][3] = 1;
	return (matrix);
}
