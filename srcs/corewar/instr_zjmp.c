/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_zjmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:26:47 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/18 13:24:49 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** JUMP
** - opcode: 0x09
** - wait: 20
** - argcode: no
** - args: DIR(2)
** - addressing retriction: yes
** - carry: no
** - description: If the carry is 1, move the proc by the number of bytes
**   indicated by the argument.
*/

void	instr_zjmp(t_cor *cor, t_proc *proc)
{
	proc->move = get_short_arg_value(cor, proc->idx + 1);
	if (cor->verbose & V_OPERATIONS)
	{
		ft_printf("P %4d | zjmp %d ", proc->n, proc->move);
		if (proc->carry)
			ft_printf("OK\n");
		else
			ft_printf("FAILED\n");
	}
	proc->move %= IDX_MOD;
	if (!proc->carry)
		proc->move = 3;
}
