/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3_axis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:50:56 by jayache           #+#    #+#             */
/*   Updated: 2018/12/01 17:27:27 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector3	ft_vector3_axis(t_vector3 vec1, t_vector3 vec2)
{
	return (ft_vector3_normalize(ft_vector3(vec1.x * vec2.x, vec1.y * vec2.y,
	vec1.z * vec2.z)));
}
