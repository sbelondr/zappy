/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2_normalize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 14:48:49 by jayache           #+#    #+#             */
/*   Updated: 2018/12/01 16:12:12 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector2	ft_vector2_normalize(t_vector2 vec)
{
	float mag;

	mag = ft_vector2_magnitude(vec);
	vec.x /= mag;
	vec.y /= mag;
	return (vec);
}
