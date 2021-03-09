/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_infix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 10:14:17 by jayache           #+#    #+#             */
/*   Updated: 2019/08/09 15:47:39 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_apply_defix(t_btree *root, void (*applyf)(void *))
{
	if (!root)
		return ;
	if (root->right)
		ft_btree_apply_defix(root->right, applyf);
	applyf(root->item);
	if (root->left)
		ft_btree_apply_defix(root->left, applyf);
}
