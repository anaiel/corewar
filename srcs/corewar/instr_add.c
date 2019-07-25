/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:18:49 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/21 11:33:32 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** ADDITION
** - opcode: 0x04
** - wait: 10
** - argcode: yes
** - args: REG REG REG
** - addressing retriction: no
** - carry: 1 if the sum is 0, 0 otherwise
** - description: Adds the content of the registers indicated by the first and
**   second arguments, and stores the result in the third register.
*/

void		instr_add(t_cor *cor, t_proc *proc)
{
	int		sum;
	int		src1;
	int		src2;

	if (get_args(cor, proc))
	{
		src1 = get_reg_value(proc->regs[cor->args[0].val - 1]);
		src2 = get_reg_value(proc->regs[cor->args[1].val - 1]);
		sum = src1 + src2;
		proc->carry = (!sum);
		regcpy(proc->regs[cor->args[2].val - 1], (void *)&sum);
		if (cor->verbose & V_OPERATIONS)
			ft_printf("P %4d | add r%d r%d r%d\n", proc->n, cor->args[0].val,
					cor->args[1].val, cor->args[2].val);
	}
}
