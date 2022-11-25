/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:15:12 by jayache           #+#    #+#             */
/*   Updated: 2022/11/25 16:26:25 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

int	delta_to_time(int delta)
{
	int				ret;
	double			time;

	time = 1.0 / delta;
	ret = time * 1000;
	return (ret);
}

clock_t delta_to_clock_t(int delta)
{
	double			time;

	time = 1.0 / delta;
	return (time * CLOCKS_PER_SEC);
}
