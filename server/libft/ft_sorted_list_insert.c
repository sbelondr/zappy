/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_list_insert.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 14:23:00 by jayache           #+#    #+#             */
/*   Updated: 2019/12/08 09:52:46 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sorted_list_insert(t_list **begin_list, void *data, int (*cmp)())
{
	t_list	*elem;
	t_list	*temp;
	int		inserted;

	inserted = 0;
	elem = *begin_list;
	temp = NULL;
	while (elem && !inserted)
	{
		if (cmp(elem->content, data) >= 0)
		{
			temp->next = ft_lstnew(data, sizeof(data));
			temp->next->next = elem;
			inserted = 1;
		}
		if (elem->next == NULL && !inserted)
		{
			elem->next = ft_lstnew(data, sizeof(data));
			inserted = 1;
		}
		temp = elem;
		elem = elem->next;
	}
	if (!inserted)
		*begin_list = ft_lstnew(data, sizeof(data));
}
