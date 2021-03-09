/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:48:12 by jayache           #+#    #+#             */
/*   Updated: 2018/11/12 15:08:34 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

static char	*initstritoa(long n, int neg)
{
	char	*str;

	if (neg == 1)
		str = ft_strnew(sizeof(char) * 1);
	else
		str = ft_strnew(sizeof(char) * 2);
	if (!str)
		return (NULL);
	if (neg == 1)
		str[0] = n + '0';
	else
	{
		str[0] = '-';
		str[1] = n + '0';
	}
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		neg;
	char	*s1;
	char	*s2;
	long	sn;

	sn = ft_abs(n);
	neg = ft_sign(n);
	if (sn < 10)
		return (initstritoa(sn, neg));
	s2 = ft_itoa(sn % (10));
	s1 = ft_itoa(sn / (10));
	str = (ft_strjoin(s1, s2));
	if (!str || !s1 || !s2)
		return (NULL);
	free(s1);
	free(s2);
	if (neg == -1)
	{
		s1 = str;
		str = ft_strjoin("-", s1);
		free(s1);
	}
	return (str);
}
