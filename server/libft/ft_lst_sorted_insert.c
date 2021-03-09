/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_list_insert.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 14:23:00 by jayache           #+#    #+#             */
/*   Updated: 2019/12/08 09:55:05 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_sorted_insert(t_list **begin_list, t_list *data, int (*cmp)())
{
	t_list *start;
	t_list *prev;

	start = *begin_list;
	prev = NULL;
	while (start)
	{
		if (cmp(data->content, start->content) <= 0)
		{
			if (prev)
				prev->next = data;
			else
				*begin_list = data;
			data->next = start;
			return ;
		}
		prev = start;
		start = start->next;
	}
	if (!start)
		ft_lst_append(begin_list, data);
}
