/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_arenas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:28:54 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/01 11:52:59 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	draw_starting_arena(t_cor *cor)
{
	int i;
	int j;
	int idx;

	idx = 0;
	i = -1;
	while (++i < MEM_SIZE)
		cor->visu->attr_arena[i].owner = 0;
	i = -1;
	while (++i < cor->nb_champs)
	{
		j = -1;
		while (++j < (int)cor->champs[i]->head.prog_size)
			cor->visu->attr_arena[idx + j].owner = cor->champs[i]->player_no;
		idx += MEM_SIZE / cor->nb_champs;
	}
}

void	manager(t_cor *cor, int key)
{
	if (key == ' ')
		cor->visu->is_running = !cor->visu->is_running;
	else if (key == 'q' || key == 'w' || key == 'e' || key == 'r')
	{
		modify_speed_factor(cor, key);
		apply_speed(cor);
	}
	draw_arenas(cor);
}

void	draw_arenas(t_cor *cor)
{
	if (cor->curr_cycle != 1 && cor->visu->is_running == false)
	{
		wmove(cor->visu->arena_info, 2, 3);
		wprintw(cor->visu->arena_info, "** PAUSED ** ");
		wmove(cor->visu->arena_info, 6, 3);
		wprintw(cor->visu->arena_info, "Cycle : %d  ", cor->curr_cycle);
		wrefresh(cor->visu->arena_info);
	}
	else
	{
		manage_arena(cor);
		manage_arena_info(cor);
		manage_arena_period_bar(cor);
	}
}
