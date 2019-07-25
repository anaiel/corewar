/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:21:23 by anyahyao          #+#    #+#             */
/*   Updated: 2019/06/27 19:41:45 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long		ft_atoll(const char *s)
{
	unsigned long long	res;
	int					sign;

	res = 0;
	sign = 1;
	while (*s && ft_isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s && ft_isdigit(*s))
	{
		if (res > 922337203685477580)
			return ((sign > 0 ? LLONG_MAX : LLONG_MIN));
		res = res * 10 + *s - '0';
		s++;
	}
	if (res > LLONG_MAX)
		return ((sign > 0 ? LLONG_MAX : LLONG_MIN));
	return ((res * sign));
}
