/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_xor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:22:34 by dtrigalo          #+#    #+#             */
/*   Updated: 2019/06/21 11:32:18 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** XOR
** - opcode: 0x08
** - wait: 6
** - argcode: yes
** - args: REG/IND/DIR(4) REG/IND/DIR(4) REG
** - addressing retriction: yes
** - carry: 1 if the result of the '^' is 0, 0 otherwise
** - description: Stores the result of the bitwise '^' operation between the
**   first and second arguments in the register indicated by the third argument
*/

void		instr_xor(t_cor *cor, t_proc *proc)
{
	int		src1;
	int		src2;
	int		tmp;

	if (get_args(cor, proc))
	{
		src1 = get_arg_true_val(cor, proc, cor->args[0], true);
		src2 = get_arg_true_val(cor, proc, cor->args[1], true);
		tmp = src1 ^ src2;
		proc->carry = (!tmp);
		regcpy(proc->regs[cor->args[2].val - 1], (void *)&tmp);
		if (cor->verbose & V_OPERATIONS)
			ft_printf("P %4d | xor %d %d r%d\n", proc->n, src1, src2,
					cor->args[2].val);
	}
}
