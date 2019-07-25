/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_color_panel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:35:15 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/02 15:38:57 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	create_color_panel(void)
{
	use_default_colors();
	start_color();
	init_color(COLOR_GRAY, 300, 300, 300);
	init_color(BLACK, 0, 0, 0);
	init_color(WHITE, 1000, 1000, 1000);
	init_pair(GRAY, COLOR_GRAY, BLACK);
	init_pair(GRAY_CURSOR, COLOR_GRAY, COLOR_GRAY);
	init_pair(RED, COLOR_RED, BLACK);
	init_pair(RED_CURSOR, BLACK, COLOR_RED);
	init_pair(RED_LIVE, WHITE, COLOR_RED);
	init_pair(GREEN, COLOR_GREEN, BLACK);
	init_pair(GREEN_CURSOR, BLACK, COLOR_GREEN);
	init_pair(GREEN_LIVE, WHITE, COLOR_GREEN);
	init_pair(YELLOW, COLOR_YELLOW, BLACK);
	init_pair(YELLOW_CURSOR, BLACK, COLOR_YELLOW);
	init_pair(YELLOW_LIVE, WHITE, COLOR_YELLOW);
	init_pair(BLUE, COLOR_BLUE, BLACK);
	init_pair(BLUE_CURSOR, BLACK, COLOR_BLUE);
	init_pair(BLUE_LIVE, WHITE, COLOR_BLUE);
	init_pair(SPEED_HIGHLIGHT, BLACK, WHITE);
}
