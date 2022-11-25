/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:26:01 by sbelondr          #+#    #+#             */
/*   Updated: 2022/11/03 10:51:04 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	set_color(t_colors color, int flags)
{
	if (flags & FLAG_COLOR)
		printf("\033[0;%dm", color);
}
