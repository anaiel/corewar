/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:28:38 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/02 15:30:35 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*parse_flag(char *str, t_specs *specs)
{
	if (specs->flags & FLAG_SPACE)
		str = flag_space(str, specs);
	if (specs->flags & FLAG_OCTO)
		str = flag_hash(str, specs);
	if (specs->flags & FLAG_PLUS)
		str = flag_plus(str, specs);
	if (specs->flags & FLAG_ZERO)
		str = flag_zero(str, specs);
	if (specs->flags & FLAG_MIN)
		str = flag_minus(str, specs);
	return (str);
}
