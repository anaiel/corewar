/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:06:27 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/11 15:09:05 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

int				ft_strccpy(char **l, t_gnl *gnl, char c, int k)
{
	int				i;
	int				ok;

	i = -1;
	ok = 1;
	(*l)[k] = '\0';
	while (gnl->str[++i] && gnl->str[i] != c)
	{
		if (ok && k > (BUFF_SIZE - 1) * gnl->len)
		{
			if (k > 100000)
				return (-1);
			ok = 0;
			gnl->len++;
			if (!(*l = (char *)realloc(*l, sizeof(char) *
							(((gnl->len) * BUFF_SIZE) + 1))))
				return (-1);
		}
		(*l)[k] = (char)gnl->str[i];
		k++;
	}
	(*l)[k] = '\0';
	return (i);
}
