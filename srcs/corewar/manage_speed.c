/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_speed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:22:44 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/01 12:12:32 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	wait_time(t_cor *cor, int time)
{
	int		t;
	int		key;

	t = clock();
	while (clock() - t < (unsigned long)time)
	{
		key = wgetch(stdscr);
		if (key != -1 && (key == 'q' || key == 'w' || key == 'e' || key == 'r'
					|| key == ' '))
			break ;
	}
	if (key != -1 && (key == 'q' || key == 'w' || key == 'e' || key == 'r'
				|| key == ' '))
		manager(cor, key);
}

static void	wait_time_very_slow(t_cor *cor)
{
	int		t;
	int		key;

	t = clock();
	while (clock() - t < VERY_SLOW)
	{
		key = wgetch(stdscr);
		if (key != -1 && (key == 'e' || key == 'r' || key == ' '))
			break ;
	}
	if (key != -1 && (key == 'e' || key == 'r' || key == ' '))
		manager(cor, key);
}

void		apply_speed(t_cor *cor)
{
	int key;

	if (cor->visu->speed == -2)
		wait_time_very_slow(cor);
	else if (cor->visu->speed == -1)
		wait_time(cor, SLOW);
	else if (cor->visu->speed == 0)
		wait_time(cor, NORMAL);
	else if (cor->visu->speed == 1)
		wait_time(cor, FAST);
	else if (cor->visu->speed == 2)
	{
		key = wgetch(stdscr);
		if (key != -1 && (key == 'q' || key == 'w' || key == ' '))
			manager(cor, key);
	}
	draw_arenas(cor);
}

void		modify_speed_factor(t_cor *cor, int key)
{
	if (key == 'q')
		cor->visu->speed = -2;
	else if (key == 'w' && cor->visu->speed != -2)
		cor->visu->speed -= 1;
	else if (key == 'e' && cor->visu->speed != 2)
		cor->visu->speed += 1;
	else if (key == 'r')
		cor->visu->speed = 2;
	wmove(cor->visu->arena_info, 4, 3);
	wprintw(cor->visu->arena_info, "Speed : << | < | o | > | >>");
	wattron(cor->visu->arena_info, COLOR_PAIR(SPEED_HIGHLIGHT));
	highlight_speed_button(cor);
	wattroff(cor->visu->arena_info, COLOR_PAIR(SPEED_HIGHLIGHT));
	wrefresh(cor->visu->arena_info);
}

void		highlight_speed_button(t_cor *cor)
{
	if (cor->visu->speed == -2)
	{
		wmove(cor->visu->arena_info, 4, 11);
		wprintw(cor->visu->arena_info, "<<");
	}
	else if (cor->visu->speed == -1)
	{
		wmove(cor->visu->arena_info, 4, 16);
		wprintw(cor->visu->arena_info, "<");
	}
	else if (cor->visu->speed == 0)
	{
		wmove(cor->visu->arena_info, 4, 20);
		wprintw(cor->visu->arena_info, "o");
	}
	else if (cor->visu->speed == 1)
	{
		wmove(cor->visu->arena_info, 4, 24);
		wprintw(cor->visu->arena_info, ">");
	}
	else if (cor->visu->speed == 2)
	{
		wmove(cor->visu->arena_info, 4, 28);
		wprintw(cor->visu->arena_info, ">>");
	}
}
