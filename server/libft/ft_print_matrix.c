/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 22:26:21 by jayache           #+#    #+#             */
/*   Updated: 2019/08/31 15:22:45 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_print_matrix(t_matrix matrix)
{
	int	x;
	int	y;

	y = 0;
	while (y < matrix.height)
	{
		x = 0;
		while (x < matrix.width)
		{
			printf("[%f]", matrix.matrix[y][x]);
			++x;
		}
		printf("\n");
		++y;
	}
}
