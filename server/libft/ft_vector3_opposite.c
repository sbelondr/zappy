/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector3_opposite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 22:44:06 by jayache           #+#    #+#             */
/*   Updated: 2019/08/29 22:44:49 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector3	ft_vector3_opposite(t_vector3 vtc)
{
	t_vector3 vec;

	vec.x = vtc.x * -1;
	vec.y = vtc.y * -1;
	vec.z = vtc.z * -1;
	return (vec);
}
