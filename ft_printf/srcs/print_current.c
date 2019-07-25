/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_current.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 15:23:34 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/01 17:07:29 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_current(t_form *fmt)
{
	write(1, fmt->str, fmt->i);
	fmt->str += fmt->i;
	fmt->cnt += fmt->i;
	fmt->i = 0;
}
