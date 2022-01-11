/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelbyval.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 09:53:04 by jayache           #+#    #+#             */
/*   Updated: 2022/01/11 09:40:00 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstdelbyval(t_list **lst, void *data, int (*cmp)(), void (*del)())
{
	t_list *prev;
	t_list *current;

	current = *lst;
	prev = NULL;
	while (current)
	{
		if (!cmp(current->content, data))
		{
			if (prev)
				prev->next = current->next;
			else
				*lst = current->next;
			ft_lstdelone(&current, del);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
