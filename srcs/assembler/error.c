/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 19:38:38 by anyahyao          #+#    #+#             */
/*   Updated: 2019/07/11 14:38:02 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		warning_champion(t_champion *champion, char *s, int line)
{
	champion->number_warning++;
	if (line >= 0)
		ft_printf("line %d_ Warning: %s\n", line, s);
	else
		ft_printf("Warning: %s\n", s);
	return (1);
}

int		error_champion(t_champion *champion, char *s, int line)
{
	champion->number_error++;
	if (line >= 0)
		ft_printf("line %d_ Error: %s\n", line, s);
	else
		ft_printf("Error: %s\n", s);
	return (1);
}

int		malloc_error(char *str)
{
	ft_printf("Malloc error: %s", str);
	return (0);
}
