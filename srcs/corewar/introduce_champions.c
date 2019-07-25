/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   introduce_champions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 17:17:55 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/12 17:32:45 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	introduce_champions(t_cor *cor)
{
	int		i;

	ft_putendl("Introducing contestants...");
	i = -1;
	while (++i < cor->nb_champs)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
				cor->champs[i]->head.prog_size, cor->champs[i]->head.prog_name,
				cor->champs[i]->head.comment);
}
