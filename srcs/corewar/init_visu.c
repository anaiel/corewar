/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:37:00 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/01 16:51:57 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	start_set_windows(void)
{
	initscr();
	noecho();
	curs_set(0);
	cbreak();
	keypad(stdscr, true);
	nodelay(stdscr, true);
}

void		init_visu(t_cor *cor)
{
	int i;

	start_set_windows();
	if (!(cor->visu = (t_visu *)malloc(sizeof(t_visu))))
		error(cor, "Malloc of the visu has failed");
	cor->visu->arena = NULL;
	cor->visu->arena_info = NULL;
	cor->visu->arena_period_bar = NULL;
	if (!(cor->visu->arena = newwin(HEIGHT, WIDTH, 1, 1)))
		error(cor, "Visu arena newwin had failed");
	if (!(cor->visu->arena_info = newwin(HEIGHT, WIDTH / 3, 1, WIDTH + 2)))
		error(cor, "Visu arena info newwin has failed");
	if (!(cor->visu->arena_period_bar = newwin(5, WIDTH + WIDTH / 3 + 1,
			HEIGHT + 2, 1)))
		error(cor, "Visu arena announce newwin has failed");
	i = -1;
	while (++i < MEM_SIZE)
	{
		cor->visu->attr_arena[i].live_bright = 0;
		cor->visu->attr_arena[i].store_bright = 0;
		cor->visu->attr_arena[i].cursor = false;
	}
	cor->visu->is_running = false;
	cor->visu->speed = 0;
}
