/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_instr2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 11:21:48 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/21 14:02:13 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Returns the modified version of an index that insures it is within the scope
** of the VM.
*/

int		restricted_addr(int new_idx)
{
	if (new_idx < 0)
		return (MEM_SIZE + (new_idx % MEM_SIZE));
	else
		return (new_idx % MEM_SIZE);
}

/*
** Returns a short from a string of unsigned char
*/

short	get_short_arg_value(t_cor *cor, int idx)
{
	return ((short)(cor->arena[restricted_addr(idx)] * 256
				+ cor->arena[restricted_addr(idx + 1)]));
}

/*
** Returns an int from a string of unsigned char, considering size bytes.
*/

int		get_int_arg_value(t_cor *cor, int idx, int size)
{
	int		res;
	int		i;

	res = cor->arena[restricted_addr(idx)];
	i = 0;
	while (++i < size)
		res = res * 256 + cor->arena[restricted_addr(idx + i)];
	return (res);
}

/*
** Stores the content of a register on the map.
*/

void	mapcpy(t_cor *cor, t_proc *proc, unsigned int idx, void *content)
{
	int	i;

	i = -1;
	while (++i < REG_SIZE)
	{
		cor->arena[restricted_addr(idx
				+ i)] = ((unsigned char *)content)[REG_SIZE - i - 1];
		if (cor->visual_on)
		{
			cor->visu->attr_arena[restricted_addr(idx
					+ i)].owner = proc->parent_id;
			cor->visu->attr_arena[restricted_addr(idx
					+ i)].store_bright = STORE_BRIGHT_TIME;
		}
	}
}

/*
** Loads the content of the map in a register.
*/

void	regcpy(unsigned char *reg, void *content)
{
	int	i;

	i = -1;
	while (++i < REG_SIZE)
		reg[i] = ((unsigned char *)content)[i];
}
