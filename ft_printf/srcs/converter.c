/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 19:47:15 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/03 15:50:41 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*converter(t_specs *specs, va_list ap)
{
	char	*res;

	res = parse_conv(ap, specs);
	if (specs->null_char)
		specs->len = 1;
	else
		specs->len = ft_strlen(res);
	res = parse_accufield(res, specs);
	res = parse_flag(res, specs);
	return (res);
}
