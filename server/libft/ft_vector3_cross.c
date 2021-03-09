/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3_cross.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:25:08 by jayache           #+#    #+#             */
/*   Updated: 2018/12/01 16:48:31 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector3	ft_vector3_cross(t_vector3 vec1, t_vector3 vec2)
{
	return (ft_vector3(vec1.y * vec2.z - vec2.y * vec1.z, vec1.z * vec2.x -
	vec2.z * vec1.x, vec1.x * vec2.y - vec2.x * vec1.y));
}
