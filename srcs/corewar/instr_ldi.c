/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_ldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 10:27:40 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/19 09:08:23 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** INDIRECT LOAD
** - opcode: 0x0A
** - wait: 25
** - argcode: yes
** - args: REG/IND/DIR(2) REG/DIR(2) REG
** - addressing retriction: yes
** - carry: no
** - description: Stores the value of the address resulting from the sum of the
**   first two arguments in the register indicated by the third argument.
*/

void		instr_ldi(t_cor *cor, t_proc *proc)
{
	int		src1;
	int		src2;
	int		tmp;
	int		addr;

	if (get_args(cor, proc))
	{
		src1 = get_arg_true_val(cor, proc, cor->args[0], true);
		src2 = get_arg_true_val(cor, proc, cor->args[1], true);
		tmp = src1 + src2;
		addr = get_int_arg_value(cor, proc->idx + tmp % IDX_MOD, 4);
		regcpy(proc->regs[cor->args[2].val - 1], (void *)&addr);
		if (cor->verbose & V_OPERATIONS)
		{
			ft_printf("P %4d | ldi %d %d r%d\n", proc->n, src1, src2,
					cor->args[2].val);
			ft_printf("       | -> load from %d + %d = %d ", src1, src2, tmp);
			ft_printf("(with pc and mod %d)\n", proc->idx + tmp % IDX_MOD);
		}
	}
}
