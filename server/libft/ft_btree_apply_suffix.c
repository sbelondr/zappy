/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 10:10:24 by jayache           #+#    #+#             */
/*   Updated: 2019/08/09 15:09:26 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_apply_suffix(t_btree *root, void (*applyf)(void *))
{
	if (!root)
		return ;
	if (root->left)
		ft_btree_apply_suffix(root->left, applyf);
	if (root->right)
		ft_btree_apply_suffix(root->right, applyf);
	applyf(root->item);
}
