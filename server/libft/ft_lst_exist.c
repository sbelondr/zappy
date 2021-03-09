/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_exist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 09:55:18 by jayache           #+#    #+#             */
/*   Updated: 2019/12/08 09:57:03 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** RETURNS 1 IF DATA EXIST IN LIST, 0 OTHERWISE
*/

int	ft_lst_exist(t_list *root, void *data, int (cmp(void*, void*)))
{
	while (root)
	{
		if (!cmp(root->content, data))
			return (1);
		root = root->next;
	}
	return (0);
}
