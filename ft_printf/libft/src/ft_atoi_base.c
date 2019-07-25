/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:17:48 by anleclab          #+#    #+#             */
/*   Updated: 2019/04/30 14:26:02 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_atoi_base(unsigned char *str, int base)
{
	unsigned int	res;
	int				i;

	if (base < 2 || base > 16)
		return (0);
	res = 0;
	i = -1;
	while (str[++i])
		if (str[i] >= '0' && str[i] <= '9' && str[i] < base + '0')
			res += str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F' && str[i] < base - 10 + 'A')
			res += str[i] - 'A';
		else if (str[i] >= 'a' && str[i] <= 'f' && str[i] < base - 10 + 'a')
			res += str[i] - 'a';
		else
			return (0);
	return (res);
}
