/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:26:01 by sbelondr          #+#    #+#             */
/*   Updated: 2022/02/23 10:10:29 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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
