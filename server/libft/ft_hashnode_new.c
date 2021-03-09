/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashnode_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 10:01:51 by jayache           #+#    #+#             */
/*   Updated: 2019/12/08 10:01:58 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** USED FOR HASHTABLE
*/

t_hashnode	*ft_hashnode_new(char *index, void *val)
{
	t_hashnode	*node;

	node = (t_hashnode*)malloc(sizeof(t_hashnode));
	node->key = index;
	node->content = val;
	return (node);
}
