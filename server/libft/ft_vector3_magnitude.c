/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3_magnitude.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 14:55:28 by jayache           #+#    #+#             */
/*   Updated: 2019/08/31 15:06:59 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_vector3_magnitude(t_vector3 vec)
{
	return (sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
}
