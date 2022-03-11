/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelondr <sbelondr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:26:08 by sbelondr          #+#    #+#             */
/*   Updated: 2022/03/03 08:55:48 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include <signal.h>

void	setup_signal(void)
{
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, ft_quit);
}
