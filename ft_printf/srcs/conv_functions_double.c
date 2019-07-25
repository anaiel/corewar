/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_functions_double.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:46:45 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/05 10:50:45 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*deci_part(double dbl, int accu)
{
	char	*res;
	int		i;
	double	tmp;

	if (!(res = ft_strnew(accu + 1)))
		exit_error("error: malloc failed\n", 0);
	i = -1;
	while (++i < accu)
		dbl *= 10;
	i = 0;
	while (--accu >= 0)
	{
		tmp = dbl / ft_double_power(10.0, accu);
		res[i] = '0' + (int)tmp;
		dbl -= (double)((int)tmp * ft_double_power(10.0, accu));
		i++;
	}
	return (res);
}

static char	*concat(char *s1, char *s2)
{
	char	*res;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(res = ft_strnew(len1 + len2 + 1)))
		exit_error("error: malloc failed\n", 2, s1, s2);
	ft_strncpy(res, s1, len1);
	ft_strncat(res, s2, len2);
	return (res);
}

static char	*integ_part(double *dbl)
{
	int		pow_max;
	int		i;
	double	tmp;
	char	*res;

	*dbl = (*dbl < 0 ? -*dbl : *dbl);
	tmp = *dbl;
	pow_max = 0;
	while (tmp > 10.0)
	{
		pow_max++;
		tmp /= 10;
	}
	if (!(res = ft_strnew(pow_max + 1)))
		exit_error("error: malloc failed\n", 0);
	i = 0;
	while (pow_max >= 0)
	{
		tmp = *dbl / ft_double_power(10, pow_max);
		res[i] = '0' + (int)tmp;
		*dbl -= (double)((int)tmp * ft_double_power(10, pow_max));
		pow_max--;
		i++;
	}
	return (res);
}

char		*conv_f(va_list ap, t_specs *specs)
{
	char	*res;
	double	dbl;
	char	*tmp;
	int		isneg;

	dbl = va_arg(ap, double);
	isneg = (dbl < 0 ? 1 : 0);
	res = integ_part(&dbl);
	if (specs->flags & ACCURACY)
		res = concat(concat(res, ft_strdup(".")),
				deci_part(dbl, specs->accuracy));
	if (isneg)
	{
		if (!(tmp = ft_strnew(ft_strlen(res) + 2)))
			exit_error("error:malloc failed\n", 1, res);
		tmp[0] = '-';
		ft_strncpy(tmp + 1, res, ft_strlen(res));
		free(res);
		res = tmp;
	}
	return (res);
}
