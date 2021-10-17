/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 10:13:21 by selver            #+#    #+#             */
/*   Updated: 2021/10/17 09:52:56 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

t_client *new_client(void)
{
	t_client *ret;
	
	ret = ft_memalloc(sizeof(t_client));
	ft_bzero(ret->ressource, sizeof(int) * 7);
	return (ret);
}
