/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetbypos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 22:51:21 by jayache           #+#    #+#             */
/*   Updated: 2019/08/23 23:04:09 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** RETURN THE N-MEMBER OF THE LIST
*/

t_list	*ft_lstgetbypos(t_list *lst, int pos)
{
	int	i;

	i = 0;
	if (pos <= 0)
		return (lst);
	while (i < pos && lst)
	{
		++i;
		lst = lst->next;
	}
	return (lst);
}
