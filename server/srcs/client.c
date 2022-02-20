/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 10:13:21 by selver            #+#    #+#             */
/*   Updated: 2022/02/20 15:38:47 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

t_client	*new_client(int id)
{
	t_client	*ret;

	ret = ft_memalloc(sizeof(t_client));
	ft_bzero(ret->ressource, sizeof(int) * 7);
	ret->id = id;
	ret->lvl = 1;
	ret->ressource[FOOD] = 10;
	return (ret);
}
