/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_breakdowns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 18:26:17 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/03 17:48:27 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				get_champ_color(int i)
{
	if (!i)
		return (COLOR_PAIR(RED) | A_BOLD);
	if (i == 1)
		return (COLOR_PAIR(GREEN) | A_BOLD);
	if (i == 2)
		return (COLOR_PAIR(YELLOW) | A_BOLD);
	if (i == 3)
		return (COLOR_PAIR(BLUE) | A_BOLD);
	return (COLOR_PAIR(GRAY) | A_BOLD);
}

static void		draw_curr_dash(t_cor *cor, int total, int i, int *max)
{
	int		j;
	int		attribute;

	j = -1;
	attribute = get_champ_color(i);
	wattron(cor->visu->arena_info, attribute);
	while (++j < (((double)cor->champs[i]->lives_in_curr_period * 50)
				/ total) && *max < 50)
	{
		waddch(cor->visu->arena_info, '-');
		(*max)++;
	}
	wattroff(cor->visu->arena_info, attribute);
}

static void		draw_last_dash(t_cor *cor, int total, int i, int *max)
{
	int		j;
	int		attribute;

	j = -1;
	attribute = (cor->curr_cycle >= CYCLE_TO_DIE)
		? get_champ_color(i) : COLOR_PAIR(GRAY);
	wattron(cor->visu->arena_info, attribute);
	while (++j < (((double)cor->champs[i]->lives_in_last_period * 50)
				/ total) && *max < 50)
	{
		waddch(cor->visu->arena_info, '-');
		(*max)++;
	}
	wattroff(cor->visu->arena_info, attribute);
}

void			draw_current_live(t_cor *cor)
{
	int		i;
	int		total;
	int		max;

	i = -1;
	total = 0;
	while (++i < cor->nb_champs)
		total += cor->champs[i]->lives_in_curr_period;
	if (total == 0)
		wprintw(cor->visu->arena_info,
				"--------------------------------------------------");
	else
	{
		i = -1;
		while (++i < cor->nb_champs)
			draw_curr_dash(cor, total, i, &max);
		while (max++ < 50)
			waddch(cor->visu->arena_info, '-');
	}
	waddch(cor->visu->arena_info, ']');
}

void			draw_last_live(t_cor *cor)
{
	int		i;
	int		total;
	int		max;

	i = -1;
	total = 0;
	max = 0;
	while (++i < cor->nb_champs)
		total += cor->champs[i]->lives_in_last_period;
	if (total == 0)
		wprintw(cor->visu->arena_info,
				"--------------------------------------------------");
	else
	{
		i = -1;
		while (++i < cor->nb_champs)
			draw_last_dash(cor, total, i, &max);
		while (max++ < 50)
			waddch(cor->visu->arena_info, '-');
	}
	waddch(cor->visu->arena_info, ']');
}
