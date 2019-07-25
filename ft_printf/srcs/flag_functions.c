/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:11:40 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/05 10:59:28 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*flag_hash(char *str, t_specs *specs)
{
	char	*ret;
	int		i;
	int		j;

	if (specs->conv == 'o' || specs->conv == 'x' || specs->conv == 'X')
	{
		ret = str;
		i = 0;
		while (str[i] && str[i] == ' ')
			i++;
		j = i;
		while (str[j] == '0')
			j++;
		if (!str[j])
			return (str);
		if (specs->conv == 'o' && str[i] != '0')
			ret = suffix("0", str);
		else if (specs->conv == 'x')
			ret = suffix("0x", str);
		else if (specs->conv == 'X')
			ret = suffix("0X", str);
		specs->len = ft_strlen(ret);
		return (ret);
	}
	return (str);
}

char	*flag_space(char *str, t_specs *specs)
{
	char	*res;
	int		i;

	i = -1;
	while (str[++i] == ' ')
		;
	if ((specs->conv == 'd' || specs->conv == 'i' || specs->conv == 'f')
			&& str[i] != '-')
	{
		res = suffix(" ", str);
		specs->len = ft_strlen(res);
		return (res);
	}
	return (str);
}

char	*flag_plus(char *str, t_specs *specs)
{
	char	*ret;

	if ((specs->conv == 'd' || specs->conv == 'i'
			|| specs->conv == 'f') && !ft_strchr(str, '-'))
	{
		ret = suffix("+", str);
		specs->len = ft_strlen(ret);
		return (ret);
	}
	return (str);
}

char	*flag_minus(char *str, t_specs *specs)
{
	int		i;
	int		j;

	if (specs->null_char)
	{
		str[specs->len - 1] = ' ';
		*str = 0;
		return (str);
	}
	i = 0;
	while (str[i] == ' ')
		i++;
	j = ((specs->flags & FLAG_SPACE) && str[0] == ' ' && str[i] != '-') ? 1 : 0;
	if (j != i)
	{
		while (str[i])
			str[j++] = str[i++];
		while (str[j])
			str[j++] = ' ';
	}
	return (str);
}

char	*flag_zero(char *str, t_specs *specs)
{
	int		i;

	i = (specs->flags & FLAG_SPACE && str[0] == ' ') ? 0 : -1;
	(void)specs;
	while (str[++i] == ' ')
		str[i] = '0';
	if (str[i] == '\t')
	{
		str[i++] = '0';
		str[0] = '\t';
	}
	if (i && (str[i] == '-' || str[i] == '+'))
	{
		str[0] = (str[i] == '-' ? '-' : '+');
		str[i] = '0';
	}
	if (i && (str[i + 1] == 'x' || str[i + 1] == 'X'))
	{
		str[1] = (str[i + 1] == 'x' ? 'x' : 'X');
		str[i + 1] = '0';
	}
	return (str);
}
