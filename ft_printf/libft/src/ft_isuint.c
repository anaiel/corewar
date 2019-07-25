/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isuint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 13:25:58 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/03 14:59:51 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isuint(char *str)
{
	int		i;
	char	last_digit;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	if (ft_strlen(str) > 10)
		return (0);
	if (ft_strlen(str) < 10)
		return (1);
	last_digit = str[ft_strlen(str) - 1];
	str[ft_strlen(str) - 1] = 0;
	if ((unsigned int)ft_atoi(str) > UINT_MAX / 10
			|| ((unsigned int)ft_atoi(str) == UINT_MAX / 10
				&& last_digit > 5))
		return (0);
	return (1);
}
