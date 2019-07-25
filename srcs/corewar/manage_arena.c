/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arena.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:21:05 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/27 12:47:45 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	boxing(WINDOW *window)
{
	wattron(window, COLOR_PAIR(GRAY_CURSOR));
	box(window, '*', '*');
	wattroff(window, COLOR_PAIR(GRAY_CURSOR));
}

void	manage_arena(t_cor *cor)
{
	int i;
	int j;
	int attribute;

	werase(cor->visu->arena);
	wprintw(cor->visu->arena, "\n\n");
	i = -1;
	while (++i < MEM_SIZE / 64)
	{
		j = -1;
		wprintw(cor->visu->arena, "  ");
		while (++j < MEM_SIZE / 64)
		{
			attribute = get_attribute(cor, i * 64 + j);
			waddch(cor->visu->arena, ' ');
			wattron(cor->visu->arena, attribute);
			wprintw(cor->visu->arena, "%.2x", cor->arena[i * 64 + j]);
			wattroff(cor->visu->arena, attribute);
			cor->visu->attr_arena[i * 64 + j].cursor = false;
		}
		wprintw(cor->visu->arena, " \n");
	}
	boxing(cor->visu->arena);
	wrefresh(cor->visu->arena);
}
