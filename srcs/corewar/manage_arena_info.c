/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arena_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 10:06:35 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/01 12:16:05 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		draw_constants_arena_info(t_cor *cor, int y)
{
	y += 3;
	wmove(cor->visu->arena_info, y, 3);
	wprintw(cor->visu->arena_info, "CYCLE_TO_DIE : %d", cor->cycle_to_die);
	y += 2;
	wmove(cor->visu->arena_info, y, 3);
	wprintw(cor->visu->arena_info, "CYCLE_DELTA : %d", CYCLE_DELTA);
	y += 2;
	wmove(cor->visu->arena_info, y, 3);
	wprintw(cor->visu->arena_info, "NBR_LIVE : %d", NBR_LIVE);
	y += 2;
	wmove(cor->visu->arena_info, y, 3);
	wprintw(cor->visu->arena_info, "MAX_CHECKS : %d", MAX_CHECKS);
}

static void		draw_cycle_proc_arena_info(t_cor *cor, int *y)
{
	wmove(cor->visu->arena_info, *y, 3);
	if (cor->visu->is_running)
		wprintw(cor->visu->arena_info, "** RUNNING **");
	else
		wprintw(cor->visu->arena_info, "** PAUSED **");
	*y += 4;
	wmove(cor->visu->arena_info, *y, 3);
	wprintw(cor->visu->arena_info, "Cycle : %d", cor->curr_cycle);
	*y += 2;
	wmove(cor->visu->arena_info, *y, 3);
	wprintw(cor->visu->arena_info, "Processes : %d", cor->nb_procs);
}

static void		draw_live_breakdowns(t_cor *cor, int *y)
{
	*y += 2;
	wmove(cor->visu->arena_info, *y, 3);
	wprintw(cor->visu->arena_info, "Live breakdown for current period :");
	wmove(cor->visu->arena_info, ++(*y), 3);
	waddch(cor->visu->arena_info, '[');
	draw_current_live(cor);
	*y += 2;
	wmove(cor->visu->arena_info, *y, 3);
	wprintw(cor->visu->arena_info, "Live breakdown for last period :");
	wmove(cor->visu->arena_info, ++(*y), 3);
	waddch(cor->visu->arena_info, '[');
	draw_last_live(cor);
}

static void		draw_player_infos(t_cor *cor, int *y, int i)
{
	int attribute;

	*y += 3;
	wmove(cor->visu->arena_info, *y, 3);
	wprintw(cor->visu->arena_info, "Player -%d : ",
			cor->champs[i]->player_no);
	attribute = get_champ_color(i);
	wattron(cor->visu->arena_info, attribute);
	wprintw(cor->visu->arena_info, "%s", cor->champs[i]->head.prog_name);
	wattroff(cor->visu->arena_info, attribute);
	*y += 1;
	wmove(cor->visu->arena_info, *y, 5);
	wprintw(cor->visu->arena_info, "Last live :                %d",
			cor->champs[i]->last_live);
	*y += 1;
	wmove(cor->visu->arena_info, *y, 5);
	wprintw(cor->visu->arena_info, "Lives in current period :  %d",
			cor->champs[i]->lives_in_curr_period);
}

void			manage_arena_info(t_cor *cor)
{
	int		i;
	int		y;

	y = 2;
	werase(cor->visu->arena_info);
	draw_cycle_proc_arena_info(cor, &y);
	i = -1;
	while (++i < cor->nb_champs)
		draw_player_infos(cor, &y, i);
	draw_live_breakdowns(cor, &y);
	draw_constants_arena_info(cor, y);
	boxing(cor->visu->arena_info);
	wmove(cor->visu->arena_info, 4, 3);
	wprintw(cor->visu->arena_info, "Speed : << | < | o | > | >>");
	wattron(cor->visu->arena_info, COLOR_PAIR(SPEED_HIGHLIGHT));
	highlight_speed_button(cor);
	wattroff(cor->visu->arena_info, COLOR_PAIR(SPEED_HIGHLIGHT));
	wrefresh(cor->visu->arena_info);
}
