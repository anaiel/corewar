/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 11:39:22 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/03 14:55:09 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*init_base(int base)
{
	char	*charbase;
	int		i;

	if (base < 2 || base > 16)
		return (NULL);
	if (!(charbase = ft_strnew(base + 1)))
		return (NULL);
	i = 0;
	while (i < base && i < 10)
	{
		charbase[i] = '0' + i;
		i++;
	}
	while (i < base)
	{
		charbase[i] = i - 10 + 'a';
		i++;
	}
	return (charbase);
}

static int	nb_digits(unsigned long long nb, int base)
{
	int		nbdigits;

	nbdigits = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nbdigits++;
		nb /= base;
	}
	return (nbdigits);
}

char		*ft_llitoa_base(unsigned long long n, int base)
{
	char			*charbase;
	char			*res;
	int				nbdigits;
	int				i;

	if (!(charbase = init_base(base)))
		return (NULL);
	nbdigits = nb_digits(n, base);
	if (!(res = ft_strnew(nbdigits)))
		return (NULL);
	i = -1;
	while (++i < nbdigits)
	{
		res[nbdigits - 1 - i] = charbase[n % base];
		n /= base;
	}
	free(charbase);
	return (res);
}
