/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:02:20 by jayache           #+#    #+#             */
/*   Updated: 2018/12/22 16:09:39 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_arg	init_arg(void)
{
	t_arg arg;

	arg.flags = ft_strnew(sizeof(char) * 5);
	arg.conversion = ft_strnew(sizeof(char) * 3);
	arg.str = NULL;
	arg.minimum = 0;
	arg.precision = -1;
	arg.type = '\0';
	arg.size = 0;
	return (arg);
}

static int		parsecolor(t_arg *arg, const char *str, int x)
{
	int i;

	i = 0;
	if (str[x] != '{')
		return (0);
	while (str[x + i] != '}' && str[x + i])
		++i;
	free(arg->flags);
	arg->flags = ft_strndup(str + 1 + x, i - 1);
	arg->type = 'K';
	return (i + 2);
}

static int		parsearg1(t_arg *arg, const char *str, int x)
{
	int c;

	c = 0;
	while (ft_strpbrk(str + x, " #0-+\0") == 0)
	{
		if (!ft_strchr(arg->flags, str[x]))
			arg->flags[c++] = str[x];
		++x;
	}
	if (ft_isdigit(str[x]))
	{
		arg->minimum = ft_atoi(str + x);
		x += ft_nblen(arg->minimum);
	}
	if (str[x] == '.')
	{
		arg->precision = ft_atoi(str + x + 1);
		if (!ft_isdigit(str[x + 1]))
			x -= 1;
		x += (ft_nblen(arg->precision) + 1);
	}
	return (x);
}

t_arg			parsearg(const char *str, int x)
{
	t_arg	arg;
	int		a;
	int		b;

	a = x;
	arg = init_arg();
	++x;
	b = parsecolor(&arg, str, x);
	if (b != 0)
	{
		arg.size = b;
		return (arg);
	}
	x = parsearg1(&arg, str, x);
	while (ft_strpbrk(str + x, "jhlzL") == 0)
	{
		if (b > 1)
			invalid_arg(arg, NULL, NULL);
		arg.conversion[b] = str[x];
		++x;
		++b;
	}
	arg.type = str[x];
	arg.size = 1 + x - a;
	return (arg);
}
