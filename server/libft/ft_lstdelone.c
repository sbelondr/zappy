/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:21:37 by jayache           #+#    #+#             */
/*   Updated: 2018/11/09 15:30:48 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	ft_lstdelone(t_list **alst, void (*dsl)(void *, size_t))
{
	dsl((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}
