/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:19:05 by jayache           #+#    #+#             */
/*   Updated: 2018/12/05 11:20:43 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_matrix_free(t_matrix m)
{
	int y;

	y = 0;
	while (y < m.height)
	{
		free(m.matrix[y]);
		++y;
	}
	free(m.matrix);
}