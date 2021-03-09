/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_suffix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 10:10:24 by jayache           #+#    #+#             */
/*   Updated: 2019/08/11 16:31:10 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_free(t_btree *root)
{
	if (!root)
		return ;
	if (root->left)
		ft_btree_free(root->left);
	if (root->right)
		ft_btree_free(root->right);
	free(root);
}
