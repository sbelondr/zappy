/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 12:13:37 by jayache           #+#    #+#             */
/*   Updated: 2019/12/08 09:55:45 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_append(t_list **root, t_list *append)
{
	t_list *head;

	head = *root;
	while (head && head->next)
		head = head->next;
	if (!head)
		*root = append;
	else
		head->next = append;
}
