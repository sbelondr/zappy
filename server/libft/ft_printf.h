/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:39:03 by jayache           #+#    #+#             */
/*   Updated: 2018/12/12 11:24:31 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

typedef struct	s_fd
{
	long		size;
	int			*fd;
	int			*moment;
}				t_fd;

typedef struct	s_buffer
{
	char		*buffer;
	int			bufx;
	int			size;
	t_fd		fd;
}				t_buffer;

typedef struct	s_arg
{
	int			precision;
	int			minimum;
	int			type;
	int			size;
	char		*conversion;
	char		*flags;
	char		*str;
}				t_arg;

int				ft_printf(const char *format, ...);
int				print_arg_nbr(t_arg arg, t_buffer *buf, char *str);
void			ft_printf_putchar(t_arg arg, t_buffer *buf, va_list *ap);
void			invalid_arg(t_arg arg, t_buffer *buf, va_list *ap);
void			ft_printf_putnbr(t_arg arg, t_buffer *buf, va_list *ap);
void			ft_printf_putstr(t_arg arg, t_buffer *buf, va_list *ap);
void			ft_printf_putoct(t_arg arg, t_buffer *buf, va_list *ap);
void			ft_printf_putpercent(t_arg arg, t_buffer *buf, va_list *ap);
void			ft_printf_puthexa(t_arg arg, t_buffer *buf, va_list *ap);
void			ft_printf_putuns(t_arg arg, t_buffer *buf, va_list *ap);
void			ft_printf_putlonguns(t_arg arg, t_buffer *buf, va_list *ap);
void			ft_printf_putptr(t_arg arg, t_buffer *buf, va_list *ap);
void			ft_printf_putfloat(t_arg arg, t_buffer *buf, va_list *ap);
void			ft_printf_putbinary(t_arg arg, t_buffer *buf, va_list *ap);
void			ft_printf_putfd(t_arg arg, t_buffer *buf, va_list *ap);
void			ft_printf_putcolor(t_arg arg, t_buffer *buf, va_list *ap);
int				ft_printf_printstr(t_buffer *buf, const char *str, int x);
int				printf_putchar(t_buffer *buf, char c);
int				printf_putuchar(t_buffer *buf, int c);
int				is_signed(t_arg arg);
int				calc_blank_space(t_arg arg);
t_buffer		init_buffer(void);
t_arg			parsearg(const char *str, int x);
t_arg			arg_change_flag(t_arg arg, const char *str);
t_arg			arg_add_flag(t_arg arg, const char *str);
t_arg			arg_change_conv(t_arg arg, const char *str);
int				strpadding(t_arg arg, t_buffer *buf, int size);
void			ptolower(char *c);
void			printf_write(t_buffer buf);
int				paddingspace(t_arg arg, t_buffer *buf);
int				paddingzeros(t_arg arg, t_buffer *buf);
int				sign(t_arg arg, t_buffer *buf, char *str);
int				precision(t_arg arg, t_buffer *buf, char *str);
int				hashflag(t_arg arg, t_buffer *buf, char *str);
int				reverse_padding(t_arg arg, t_buffer *buf, int size);
int				print_arg_hexa(t_arg arg, t_buffer *buf, char *str);
int				print_arg_oct(t_arg arg, t_buffer *buf, char *str);
intmax_t		take_int_arg(t_arg arg, va_list *ap);
uintmax_t		take_unsigned_arg(t_arg arg, va_list *ap);
long double		take_double_arg(t_arg arg, va_list *ap);
void			free_arg(t_arg *arg);
void			free_buffer(t_buffer *buf);

#endif
