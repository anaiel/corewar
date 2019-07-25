/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:26:32 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/05 10:36:24 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	flag_sanitize(t_specs *specs)
{
	int		mod_sanitizer;

	if ((ft_strchr("diouxX", specs->conv) && specs->flags & ACCURACY)
			|| specs->flags & FLAG_MIN)
		if (specs->flags & FLAG_ZERO)
			specs->flags = specs->flags ^ FLAG_ZERO;
	if (specs->flags & FLAG_PLUS)
		if (specs->flags & FLAG_SPACE)
			specs->flags = specs->flags ^ FLAG_SPACE;
	mod_sanitizer = MOD_Z;
	while (mod_sanitizer)
		if (specs->mod / mod_sanitizer)
		{
			specs->mod = mod_sanitizer;
			break ;
		}
		else
			mod_sanitizer /= 2;
}

static int	is_flag(char c)
{
	if (c == '#' || c == ' ' || c == '-' || c == '+' || c == 'h' || c == 'l'
			|| c == 'j' || c == 'z' || c == '.' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

static void	set_conv_specs(t_form *fmt, t_specs *specs)
{
	specs->flags = 0;
	specs->mod = 0;
	specs->accuracy = 0;
	specs->field_width = 0;
	specs->null_char = 0;
	specs->len = 0;
	specs->conv = 0;
	while (fmt->str[fmt->i] && is_flag(fmt->str[fmt->i]))
		add_flag(fmt, specs);
	specs->conv = (fmt->str[fmt->i] == 'i') ? 'd' : fmt->str[fmt->i];
	flag_sanitize(specs);
	fmt->str += fmt->i + 1;
	fmt->i = 0;
}

void		write_arg(t_form *fmt, va_list ap)
{
	char	*res;
	t_specs	specs;

	fmt->i++;
	set_conv_specs(fmt, &specs);
	res = converter(&specs, ap);
	write(1, res, specs.len);
	fmt->cnt += specs.len;
	free(res);
	res = NULL;
	fmt->i = 0;
}
