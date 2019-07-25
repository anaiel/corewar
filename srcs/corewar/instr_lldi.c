/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_lldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 17:51:11 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/21 11:32:51 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** LONG INDIRECT LOAD
** - opcode: 0x0E
** - wait: 50
** - argcode: yes
** - args: REG/IND/DIR(2) IND/DIR(2) REG
** - addressing retriction: no
** - carry: 1 if the sum of the arguments is 0, 1 otherwise
** - description: Stores the result of the sum of the first two arguments in
**   the register indicated by the third argument.
*/

void		instr_lldi(t_cor *cor, t_proc *proc)
{
	int		src1;
	int		src2;
	int		tmp;
	int		addr;

	if (get_args(cor, proc))
	{
		src1 = get_arg_true_val(cor, proc, cor->args[0], false);
		src2 = get_arg_true_val(cor, proc, cor->args[1], false);
		tmp = src1 + src2;
		addr = get_int_arg_value(cor, proc->idx + tmp, 4);
		proc->carry = (!addr);
		regcpy(proc->regs[cor->args[2].val - 1], (void *)&addr);
		if (cor->verbose & V_OPERATIONS)
		{
			ft_printf("P %4d | lldi %d %d r%d\n", proc->n, src1, src2,
					cor->args[2]);
			ft_printf("       | -> load from %d + %d = %d ", src1, src2, tmp);
			ft_printf("(with pc and mod %d)\n",
					restricted_addr(proc->idx + tmp));
		}
	}
}
