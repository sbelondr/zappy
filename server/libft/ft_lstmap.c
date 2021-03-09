/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:43:20 by jayache           #+#    #+#             */
/*   Updated: 2018/11/12 14:55:38 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *lst2;
	t_list *lst2s;

	if (!lst || !f)
		return (NULL);
	lst2 = f(lst);
	lst2s = lst2;
	lst = lst->next;
	while (lst)
	{
		lst2->next = f(lst);
		lst = lst->next;
		lst2 = lst2->next;
	}
	return (lst2s);
}
