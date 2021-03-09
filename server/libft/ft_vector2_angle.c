/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2_angle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:22:14 by jayache           #+#    #+#             */
/*   Updated: 2018/12/01 17:24:29 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_vector2_angle(t_vector2 vec1, t_vector2 vec2)
{
	return (acos(ft_vector2_dot(ft_vector2_normalize(vec1),
	ft_vector2_normalize(vec2))));
}
