/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:26:01 by sbelondr          #+#    #+#             */
/*   Updated: 2022/11/03 10:42:59 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

void	set_color(t_colors color, int flags)
{
	if (flags & FLAG_COLOR)
		printf("\033[0;%dm", color);
}
/*
void purple(void)
{
	printf("\033[0;35m");
}

void red(void)
{
	printf("\033[0;31m");
}

void blue(void)
{
	printf("\033[0;34m");
}

void yellow(void)
{
	printf("\033[0;33m");
}

void cyan(void)
{
	printf("\033[0;36m");
}

void green(void)
{
	printf("\033[0;32m");
}

void reset(void)
{
	printf("\033[0m");
}
*/
