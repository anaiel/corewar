/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:43:24 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/02 11:16:42 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	al_isspace(const char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
			|| c == ' ')
		return (1);
	else
		return (0);
}

int			ft_atoui(const char *s)
{
	unsigned int	res;
	int				i;

	i = 0;
	res = 0;
	while (s[i] && al_isspace(s[i]))
		i++;
	while (s[i] && ft_isdigit(s[i]))
		res = res * 10 + s[i++] - '0';
	return (res);
}
