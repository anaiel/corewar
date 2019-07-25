/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 10:00:21 by anleclab          #+#    #+#             */
/*   Updated: 2019/05/06 16:27:12 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	exit_error(char *er_mess, int nbfree, ...)
{
	va_list		ap;

	write(1, er_mess, ft_strlen(er_mess));
	va_start(ap, nbfree);
	while (nbfree--)
		free(va_arg(ap, void *));
	va_end(ap);
	exit(0);
}
