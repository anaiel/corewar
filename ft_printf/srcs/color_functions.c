/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 12:14:55 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/05/06 16:24:02 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*parse_color_bold(const char *format)
{
	if (ft_strnequ(format, "{bold red}", 10))
		return ("\033[1;31m");
	if (ft_strnequ(format, "{bold green}", 12))
		return ("\033[1;32m");
	if (ft_strnequ(format, "{bold yellow}", 13))
		return ("\033[1;33m");
	if (ft_strnequ(format, "{bold blue}", 11))
		return ("\033[1;34m");
	if (ft_strnequ(format, "{bold magenta}", 14))
		return ("\033[1;35m");
	if (ft_strnequ(format, "{bold cyan}", 11))
		return ("\033[1;36m");
	if (ft_strnequ(format, "{eoc}", 5))
		return ("\033[0m");
	return (NULL);
}

char		*parse_color(const char *format)
{
	if (ft_strnequ(format, "{red}", 5))
		return ("\033[0;31m");
	if (ft_strnequ(format, "{green}", 7))
		return ("\033[0;32m");
	if (ft_strnequ(format, "{yellow}", 8))
		return ("\033[0;33m");
	if (ft_strnequ(format, "{blue}", 6))
		return ("\033[0;34m");
	if (ft_strnequ(format, "{magenta}", 9))
		return ("\033[0;35m");
	if (ft_strnequ(format, "{cyan}", 6))
		return ("\033[0;36m");
	return (parse_color_bold(format));
}

int			param_len(const char *format)
{
	int	i;

	i = 0;
	while (format[i] && format[i] != '}')
		i++;
	return (++i);
}
