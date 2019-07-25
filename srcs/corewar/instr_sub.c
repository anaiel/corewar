/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:18:49 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/20 09:59:56 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** SUBSTRACTION
** - opcode: 0x05
** - wait: 10
** - argcode: yes
** - args: REG REG REG
** - addressing retriction: no
** - carry: 1 if the substraction is 0, 0 otherwise
** - description: Substracts the content of the second register from the first
**   register and stores the result in the third register
*/

void		instr_sub(t_cor *cor, t_proc *proc)
{
	int		sub;
	int		src1;
	int		src2;

	if (get_args(cor, proc))
	{
		src1 = get_reg_value(proc->regs[cor->args[0].val - 1]);
		src2 = get_reg_value(proc->regs[cor->args[1].val - 1]);
		sub = src1 - src2;
		proc->carry = (!sub);
		regcpy(proc->regs[cor->args[2].val - 1], (void *)&sub);
		if (cor->verbose & V_OPERATIONS)
			ft_printf("P %4d | sub r%d r%d r%d\n", proc->n, cor->args[0].val,
					cor->args[1].val, cor->args[2].val);
	}
}
