/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 18:23:26 by jayache           #+#    #+#             */
/*   Updated: 2019/08/18 18:23:28 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strins(char const *string, char const *ins, int pos)
{
	char	*ret;

	if (ins)
		ret = ft_strjoin(string, ins);
	else
		return (ft_strdup(string));
	ft_strcpy(ret + pos, ins);
	ft_strcpy(ret + pos + ft_strlen(ins), string + pos);
	return (ret);
}
