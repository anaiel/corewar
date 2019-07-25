/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_aff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:08:05 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/10 17:12:59 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** AFF
** - opcode: 0x0F
** - wait: 2
** - argcode: yes
** - args: REG
** - addressing retriction: no
** - carry: 1 if the content of the argument is 0, 1 otherwise
** - description: Displays the character corresponding to the argument (mod 256)
*/

void		instr_aff(t_cor *cor, t_proc *proc)
{
	int		tmp;
	char	c;
	int		size;

	if (get_args(cor, proc))
	{
		proc->carry = !cor->args[0].val;
		if ((tmp = cor->args[0].val) < REG_NUMBER)
		{
			c = get_reg_value(proc->regs[tmp - 1]) % 256;
			size = ft_strlen(cor->aff);
			if (size == BUFF_SIZE)
				if (!(cor->aff = (char *)realloc(cor->aff, size + BUFF_SIZE)))
					error(cor, "malloc failed");
			ft_bzero(cor->aff + size, BUFF_SIZE);
			ft_strncat(cor->aff, &c, 1);
		}
		if (cor->verbose & V_OPERATIONS)
			ft_printf("P %4d | aff r%d\n", proc->n, cor->args[0].val);
		else if (!cor->visual_on)
			ft_printf("Aff: %s\n", cor->aff);
	}
}
