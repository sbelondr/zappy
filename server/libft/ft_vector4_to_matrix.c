/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector4_to_matrix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:15:12 by jayache           #+#    #+#             */
/*   Updated: 2018/12/05 11:31:28 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_matrix	ft_vector4_to_matrix(t_vector4 vec)
{
	t_matrix result;

	result = ft_matrix(1, 4);
	(result.matrix[0])[0] = vec.x;
	(result.matrix[1])[0] = vec.y;
	(result.matrix[2])[0] = vec.z;
	(result.matrix[3])[0] = vec.w;
	return (result);
}
