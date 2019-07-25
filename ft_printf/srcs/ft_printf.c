/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:47:15 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/05 10:32:23 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_form	init_struct(const char *format)
{
	t_form	fmt;

	fmt.i = 0;
	fmt.cnt = 0;
	fmt.str = format;
	return (fmt);
}

static void		write_color(t_form *fmt)
{
	char *color;

	if ((color = parse_color(fmt->str + fmt->i)))
	{
		fmt->cnt += fmt->i;
		if (!ft_strequ(color, "\033[0m"))
			write(1, color, 7);
		else
			write(1, color, 4);
		fmt->str += param_len(fmt->str + fmt->i) + fmt->i;
		fmt->i = 0;
	}
}

/*
** The main function is based on the fmt structure. While the format passed as
** an argument to the ft_printf function corresponds to a "normal"  string, the
** counter of the current character increases. If the counter is on a % or {
** character, it prints the begining of the strings, operates the necessary
** transformation (conversion or color), prints the results, and goes on the
** the same until the end of the format is reached.
*/

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	t_form		fmt;

	va_start(ap, format);
	fmt = init_struct(format);
	while (fmt.str[fmt.i])
	{
		if (fmt.str[fmt.i] == '{')
		{
			print_current(&fmt);
			write_color(&fmt);
		}
		else if (fmt.str[fmt.i] == '%')
		{
			print_current(&fmt);
			write_arg(&fmt, ap);
		}
		else
			fmt.i++;
	}
	write(1, fmt.str, fmt.i);
	va_end(ap);
	return (fmt.cnt + ft_strlen(fmt.str));
}
