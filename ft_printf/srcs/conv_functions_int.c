/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_functions_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 09:57:10 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/03 15:48:25 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*conv_d(va_list ap, t_specs *specs)
{
	long long int	res;

	res = 0;
	if (specs->mod & MOD_L)
		return (ft_litoa(va_arg(ap, long)));
	else if (specs->mod & MOD_LL)
		return (ft_llitoa(va_arg(ap, long long)));
	else if (specs->mod & MOD_H)
		res = (short int)va_arg(ap, int);
	else if (specs->mod & MOD_HH)
		res = (char)va_arg(ap, int);
	else if (specs->mod & MOD_J)
		return (ft_llitoa(va_arg(ap, intmax_t)));
	else if (specs->mod & MOD_Z)
		return (ft_llitoa(va_arg(ap, size_t)));
	else
		res = va_arg(ap, int);
	return (ft_itoa(res));
}

char	*conv_o(va_list ap, t_specs *specs)
{
	unsigned long long int	res;

	res = 0;
	if (specs->mod & MOD_L)
		res = va_arg(ap, unsigned long);
	else if (specs->mod & MOD_LL)
		res = va_arg(ap, unsigned long long);
	else if (specs->mod & MOD_H)
		res = va_arg(ap, unsigned int) & 0xFFFF;
	else if (specs->mod & MOD_HH)
		res = va_arg(ap, unsigned int) & 0xFF;
	else if (specs->mod & MOD_J)
		res = va_arg(ap, uintmax_t);
	else if (specs->mod & MOD_Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, unsigned int);
	if (res == 0)
		return (ft_strdup("0"));
	return (ft_llitoa_base(res, 8));
}

char	*conv_u(va_list ap, t_specs *specs)
{
	long long int	res;

	res = 0;
	if (specs->mod & MOD_L)
		res = va_arg(ap, unsigned long);
	else if (specs->mod & MOD_LL)
		res = va_arg(ap, unsigned long long);
	else if (specs->mod & MOD_H)
		res = va_arg(ap, unsigned int) & 0xFFFF;
	else if (specs->mod & MOD_HH)
		res = va_arg(ap, unsigned int) & 0xFF;
	else if (specs->mod & MOD_J)
		res = va_arg(ap, uintmax_t);
	else if (specs->mod & MOD_Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, unsigned int);
	return (ft_llitoa(res));
}

char	*conv_x(va_list ap, t_specs *specs)
{
	long long int	res;

	res = 0;
	if (specs->mod & MOD_L)
		res = va_arg(ap, unsigned long);
	else if (specs->mod & MOD_LL)
		res = va_arg(ap, unsigned long long);
	else if (specs->mod & MOD_H)
		res = va_arg(ap, unsigned int) & 0xFFFF;
	else if (specs->mod & MOD_HH)
		res = va_arg(ap, unsigned int) & 0xFF;
	else if (specs->mod & MOD_J)
		res = va_arg(ap, uintmax_t);
	else if (specs->mod & MOD_Z)
		res = va_arg(ap, size_t);
	else
		res = va_arg(ap, unsigned int);
	return (ft_llitoa_base(res, 16));
}

char	*conv_big_x(va_list ap, t_specs *specs)
{
	int		i;
	char	*res;

	i = -1;
	res = conv_x(ap, specs);
	while (res[++i])
		res[i] = ft_toupper(res[i]);
	return (res);
}
