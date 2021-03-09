/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 09:57:14 by jayache           #+#    #+#             */
/*   Updated: 2019/08/09 15:11:04 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*ft_btree_create_node(void *item)
{
	t_btree *elem;

	elem = malloc(sizeof(t_btree));
	elem->item = item;
	elem->left = 0;
	elem->right = 0;
	return (elem);
}
