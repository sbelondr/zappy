/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:58:31 by jayache           #+#    #+#             */
/*   Updated: 2018/11/10 12:00:52 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *str;

	str = (unsigned char*)b;
	while (len)
	{
		(*(str + len - 1)) = c;
		len--;
	}
	return (str);
}
