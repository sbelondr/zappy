/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3_dot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:22:41 by jayache           #+#    #+#             */
/*   Updated: 2018/12/01 17:23:51 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_vector2_dot(t_vector2 vec1, t_vector2 vec2)
{
	return ((vec1.x * vec2.x) + (vec1.y * vec2.y));
}
