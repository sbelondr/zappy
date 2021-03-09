/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3_to_matrix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:40:02 by jayache           #+#    #+#             */
/*   Updated: 2018/12/05 13:41:22 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_matrix	ft_vector3_to_matrix(t_vector3 vec)
{
	return (ft_vector4_to_matrix(ft_vector4(vec.x, vec.y, vec.z, 1)));
}
