/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_ld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:04:29 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/20 10:00:07 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** DIRECT LOAD
** - opcode: 0x02
** - wait: 5
** - argcode: yes
** - args: IND/DIR(4) REG
** - addressing retriction: yes
** - carry: 1 if the first argument is 0, 0 otherwise
** - description: Loads the value of the first argument in the register
**   indicated by the second argument
*/

void		instr_ld(t_cor *cor, t_proc *proc)
{
	int		src1;

	if (get_args(cor, proc))
	{
		src1 = get_arg_true_val(cor, proc, cor->args[0], true);
		proc->carry = (!src1);
		regcpy(proc->regs[cor->args[1].val - 1], (void *)&src1);
		if (cor->verbose & V_OPERATIONS)
			ft_printf("P %4d | ld %d r%d\n", proc->n, src1, cor->args[1].val);
	}
}
