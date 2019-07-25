/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 19:19:18 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/09 19:19:41 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					*ft_strnjoin(char const *s1, char const *s2, int size)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = ft_strnew(size + ft_strlen(s2) + 1)))
		return (NULL);
	ft_strncpy(str, s1, size);
	ft_strcat(str, s2);
	return (str);
}
