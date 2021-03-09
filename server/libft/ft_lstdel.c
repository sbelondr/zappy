/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:25:18 by jayache           #+#    #+#             */
/*   Updated: 2018/11/10 11:37:46 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *save;
	t_list *save2;

	save = *alst;
	while (save)
	{
		save2 = save->next;
		ft_lstdelone(&save, del);
		save = save2;
	}
	*alst = NULL;
}
