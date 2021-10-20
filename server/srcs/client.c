/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selver <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 10:13:21 by selver            #+#    #+#             */
/*   Updated: 2021/10/18 12:27:26 by selver           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

t_client *new_client(int id)
{
	t_client *ret;
	
	ret = ft_memalloc(sizeof(t_client));
	ft_bzero(ret->ressource, sizeof(int) * 7);
	ret->id = id;
	return (ret);
}
