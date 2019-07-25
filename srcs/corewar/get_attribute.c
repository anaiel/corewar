/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attribute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 11:06:52 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/07/01 13:51:20 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	cursor_color(int owner)
{
	if (owner == 1)
		return (COLOR_PAIR(RED_CURSOR));
	if (owner == 2)
		return (COLOR_PAIR(GREEN_CURSOR));
	if (owner == 3)
		return (COLOR_PAIR(YELLOW_CURSOR));
	if (owner == 4)
		return (COLOR_PAIR(BLUE_CURSOR));
	return (COLOR_PAIR(GRAY_CURSOR));
}

static int	live_color(int owner)
{
	if (owner == 1)
		return (COLOR_PAIR(RED_LIVE));
	if (owner == 2)
		return (COLOR_PAIR(GREEN_LIVE));
	if (owner == 3)
		return (COLOR_PAIR(YELLOW_LIVE));
	if (owner == 4)
		return (COLOR_PAIR(BLUE_LIVE));
	return (COLOR_PAIR(GRAY));
}

static int	normal_color(int owner)
{
	if (owner == 1)
		return (COLOR_PAIR(RED));
	if (owner == 2)
		return (COLOR_PAIR(GREEN));
	if (owner == 3)
		return (COLOR_PAIR(YELLOW));
	if (owner == 4)
		return (COLOR_PAIR(BLUE));
	return (COLOR_PAIR(GRAY));
}

int			get_attribute(t_cor *cor, int idx)
{
	if (cor->visu->attr_arena[idx].live_bright-- > 0)
		return (live_color(cor->visu->attr_arena[idx].owner));
	if (cor->visu->attr_arena[idx].cursor)
		return (cursor_color(cor->visu->attr_arena[idx].owner));
	if (cor->visu->attr_arena[idx].store_bright-- > 0)
		return (normal_color(cor->visu->attr_arena[idx].owner) | A_BOLD);
	return (normal_color(cor->visu->attr_arena[idx].owner));
}
