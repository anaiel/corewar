/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_lfork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:39:50 by anleclab          #+#    #+#             */
/*   Updated: 2019/06/14 13:50:52 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** LONG FORK
** - opcode: 0x0C
** - wait: 1000
** - argcode: no
** - args: DIR(2)
** - addressing retriction: no
** - carry: no
** - description: Creates a new proc which is a clone of the current proc. It
**   is placed at the address indicated by the second parameter.
*/

void	instr_lfork(t_cor *cor, t_proc *proc)
{
	int		arg1;
	t_proc	*new_proc;

	arg1 = get_short_arg_value(cor, proc->idx + 1);
	new_proc = clone_proc(cor, proc);
	new_proc->wait = 0;
	new_proc->idx = restricted_addr(proc->idx + arg1);
	cor->procs = add_proc(new_proc, cor->procs);
	proc->move = 3;
	if (cor->verbose & V_OPERATIONS)
		ft_printf("P %4d | lfork %d (%d)\n", proc->n, arg1,
				proc->idx + arg1);
}
