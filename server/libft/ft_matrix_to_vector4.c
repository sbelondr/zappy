/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_to_vector4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:20:54 by jayache           #+#    #+#             */
/*   Updated: 2018/12/05 11:24:29 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector4	ft_matrix_to_vector4(t_matrix m)
{
	if (m.width != 1 || m.height != 4)
		return (ft_vector4(0, 0, 0, 0));
	else
		return (ft_vector4((m.matrix[0])[0], (m.matrix[1])[0],
		(m.matrix[2])[0], (m.matrix[3])[0]));
}
