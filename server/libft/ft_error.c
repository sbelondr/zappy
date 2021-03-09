/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:47:39 by jayache           #+#    #+#             */
/*   Updated: 2019/12/08 10:02:17 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** PRINT AN ERROR MESSAGE AND EXIT PROGRAM
*/

void	ft_error(const char *const str)
{
	int	nb;

	nb = write(2, "Fatal error: ", 13);
	if (str && nb != 0)
		nb += write(2, str, ft_strlen(str));
	exit(1);
}
