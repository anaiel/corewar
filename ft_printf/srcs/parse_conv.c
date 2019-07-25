/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:47:36 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/05 10:54:22 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		set_conv_list_char(t_conv *conv_list)
{
	conv_list[0].conv = 'c';
	conv_list[1].conv = 's';
	conv_list[2].conv = 'p';
	conv_list[3].conv = 'd';
	conv_list[4].conv = 'o';
	conv_list[5].conv = 'u';
	conv_list[6].conv = 'x';
	conv_list[7].conv = 'X';
	conv_list[8].conv = 'b';
	conv_list[9].conv = '%';
	conv_list[10].conv = 'f';
	conv_list[11].conv = 0;
}

static t_conv	*initialize_conv_functions(void)
{
	t_conv	*conv_list;

	if (!(conv_list = (t_conv *)malloc(sizeof(t_conv) * 12)))
		exit_error("error: malloc failed\n", 0);
	set_conv_list_char(conv_list);
	conv_list[0].f = &conv_c;
	conv_list[1].f = &conv_s;
	conv_list[2].f = &conv_p;
	conv_list[3].f = &conv_d;
	conv_list[4].f = &conv_o;
	conv_list[5].f = &conv_u;
	conv_list[6].f = &conv_x;
	conv_list[7].f = &conv_big_x;
	conv_list[8].f = &conv_binary;
	conv_list[9].f = &conv_percentage;
	conv_list[10].f = &conv_f;
	conv_list[11].f = NULL;
	return (conv_list);
}

char			*parse_conv(va_list ap, t_specs *specs)
{
	char	*str;
	int		i;
	t_conv	*conv_list;
	char	invalid_conv[2];

	conv_list = initialize_conv_functions();
	i = -1;
	str = NULL;
	while (conv_list[++i].f)
		if (specs->conv == conv_list[i].conv)
		{
			str = conv_list[i].f(ap, specs);
			break ;
		}
	if (!conv_list[i].conv)
	{
		invalid_conv[0] = specs->conv;
		invalid_conv[1] = 0;
		if (!(str = ft_strdup(invalid_conv)))
			exit_error("malloc failed", 1, conv_list);
	}
	free(conv_list);
	return (str);
}
