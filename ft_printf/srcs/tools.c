/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 14:54:00 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/02 15:30:43 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				move_right(char *str, int nbchar, char c)
{
	int		i;

	i = ft_strlen(str) - nbchar;
	while (str[i] == ' ')
		i++;
	if (str[i])
		return (0);
	i = ft_strlen(str) - 1;
	while (i - nbchar >= 0)
	{
		str[i] = str[i - nbchar];
		i--;
	}
	while (i >= 0)
	{
		str[i] = c;
		i--;
	}
	return (1);
}

static char		*suffix_ret(char *suf, char *str, int init_sp, int end_sp)
{
	int		len;
	char	*ret;

	len = ft_strlen(str) + ft_strlen(suf) - init_sp - end_sp;
	if (!(ret = ft_strnew(len)))
		exit_error("malloc failed", 1, str);
	ft_strncpy(ret, suf, ft_strlen(suf));
	ft_strncat(ret, str + init_sp, ft_strlen(str) - init_sp - end_sp);
	free(str);
	return (ret);
}

static char		*suffix_condition(char *suf, char *str, int init_sp)
{
	int		i;

	i = ft_strlen(suf) - 1;
	while (--init_sp >= 0 && i >= 0)
	{
		str[init_sp] = suf[i];
		i--;
	}
	if (i >= 0)
	{
		move_right(str, i + 1, '0');
		while (i >= 0)
		{
			str[i] = suf[i];
			i--;
		}
	}
	return (str);
}

char			*suffix(char *suf, char *str)
{
	int		init_sp;
	int		end_sp;

	init_sp = 0;
	while (str[init_sp] == ' ')
		init_sp++;
	end_sp = 0;
	while (str[ft_strlen(str) - 1 - end_sp] == ' ')
		end_sp++;
	if (init_sp + end_sp >= (int)ft_strlen(suf))
		return (suffix_condition(suf, str, init_sp));
	return (suffix_ret(suf, str, init_sp, end_sp));
}

unsigned char	*concatenate(unsigned char *s1, unsigned char *s2)
{
	unsigned char	*res;
	int				len1;
	int				len2;
	int				i;

	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	if (!(res = (unsigned char *)ft_strnew(len1 + len2 + 1)))
		return (NULL);
	i = -1;
	while (++i < len1)
		res[i] = s1[i];
	i = -1;
	while (++i < len2)
		res[len1 + i] = s2[i];
	free(s1);
	free(s2);
	return (res);
}
