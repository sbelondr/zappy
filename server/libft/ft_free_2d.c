/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 11:26:37 by jayache           #+#    #+#             */
/*   Updated: 2019/08/26 23:36:01 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	free a 2 dimension array
**	ARGS:	void *array -> 2d array to free
**			int	 size -> size of the array, or -1 if null-terminated
*/

void	ft_free_2d(void *array, int size)
{
	char	**tab;
	int		i;

	if (!array)
		return ;
	tab = array;
	i = 0;
	while (i < size || (size == -1 && tab[i]))
	{
		free(tab[i]);
		++i;
	}
	free(tab);
}
