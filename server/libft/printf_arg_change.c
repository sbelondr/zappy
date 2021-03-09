/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_arg_change.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 16:31:00 by jayache           #+#    #+#             */
/*   Updated: 2018/12/10 11:39:22 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_arg	arg_change_flag(t_arg arg, const char *str)
{
	if (arg.flags)
		free(arg.flags);
	arg.flags = ft_strnew(10);
	ft_strcpy(arg.flags, str);
	return (arg);
}

t_arg	arg_add_flag(t_arg arg, const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(arg.flags, str[i]))
			arg.flags[ft_strlen(arg.flags)] = str[i++];
	}
	return (arg);
}

t_arg	arg_change_conv(t_arg arg, const char *str)
{
	if (arg.conversion)
		free(arg.conversion);
	arg.conversion = ft_strdup(str);
	return (arg);
}
