/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:26:01 by sbelondr          #+#    #+#             */
/*   Updated: 2021/03/03 15:26:02 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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

void green(void)
{
	printf("\033[0;32m");
}

void reset(void)
{
	printf("\033[0m");
}