/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector2_rangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:24:40 by jayache           #+#    #+#             */
/*   Updated: 2018/12/01 16:13:39 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** GIVES THE ANGLE OF VEC2 RELATIVE TO VEC1
*/

float	ft_vector2_rangle(t_vector2 vec1, t_vector2 vec2)
{
	return (atan2(vec2.y, vec2.x) * atan2(vec1.y, vec1.x));
}
