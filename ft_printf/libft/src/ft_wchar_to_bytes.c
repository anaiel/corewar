/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar_to_bytes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 11:31:43 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/02 16:11:12 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned char	*ft_wchar_to_4bytes(wint_t c)
{
	unsigned char	*res;

	if (!(res = (unsigned char *)ft_strnew(4)))
		return (NULL);
	res[0] = (((c & (0b111 << 18)) >> 18) | 0b11110000);
	res[1] = (((c & (0b111111 << 12)) >> 12) | 0b10000000);
	res[2] = (((c & (0b111111 << 6)) >> 6) | 0b10000000);
	res[3] = ((c & 0b111111) | 0b10000000);
	return (res);
}

static unsigned char	*ft_wchar_to_3bytes(wint_t c)
{
	unsigned char	*res;

	if (!(res = (unsigned char *)ft_strnew(3)))
		return (NULL);
	res[0] = (((c & (0b1111 << 12)) >> 12) | 0b11100000);
	res[1] = (((c & (0b111111 << 6)) >> 6) | 0b10000000);
	res[2] = ((c & 0b111111) | 0b10000000);
	return (res);
}

static unsigned char	*ft_wchar_to_2bytes(wint_t c)
{
	unsigned char	*res;

	if (!(res = (unsigned char *)ft_strnew(2)))
		return (NULL);
	res[0] = (((c & (0b11111 << 6)) >> 6) | 0b11000000);
	res[1] = ((c & 0b111111) | 0b10000000);
	return (res);
}

unsigned char			*ft_wchar_to_bytes(wint_t c)
{
	unsigned char	*res;

	if (c > 0b1111111111111111)
		res = ft_wchar_to_4bytes(c);
	else if (c > 0b11111111111)
		res = ft_wchar_to_3bytes(c);
	else if (c > 0b1111111)
		res = ft_wchar_to_2bytes(c);
	else
	{
		if (!(res = (unsigned char *)ft_strnew(1)))
			return (NULL);
		res[0] = (unsigned char)c;
	}
	return (res);
}
