/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anleclab <anleclab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:28:41 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/10 17:25:56 by anleclab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Function that returns the true numeric value of an arguments depending on its
** type
*/

int					get_arg_true_val(t_cor *cor, t_proc *proc, t_arg arg,
		bool addr_restriction)
{
	if (arg.type == T_REG)
		return (get_reg_value(proc->regs[arg.val - 1]));
	if (arg.type == T_IND)
	{
		if (addr_restriction)
			return (get_int_arg_value(cor, proc->idx + arg.val % IDX_MOD, 4));
		else
			return (get_int_arg_value(cor, proc->idx + arg.val, 4));
	}
	if (arg.type == T_DIR)
		return (arg.val);
	return (0);
}

/*
** Returns the type of the ith argument following the argcode
*/

static t_arg_type	get_arg_type(unsigned char argcode, int i)
{
	unsigned char	argcode_bits;
	unsigned char	type;

	argcode_bits = 0b11000000 >> (2 * i);
	type = (argcode & argcode_bits) >> (6 - 2 * i);
	if (type == REG_CODE)
		return (T_REG);
	else if (type == DIR_CODE)
		return (T_DIR);
	else if (type == IND_CODE)
		return (T_IND);
	return (0);
}

/*
** Function that gets the correct value depending on the arg type
*/

static void			get_arg(t_cor *cor, t_proc *proc, int *arg_idx, int i)
{
	if (cor->args[i].type == T_REG)
	{
		cor->args[i].val = cor->arena[restricted_addr(proc->idx + *arg_idx)];
		*arg_idx += 1;
	}
	else if (cor->args[i].type == T_DIR)
	{
		cor->args[i].val = (cor->op_tab[proc->opcode - 1].dir_size == 4) ?
				get_int_arg_value(cor, proc->idx + *arg_idx, DIR_SIZE)
				: get_short_arg_value(cor, proc->idx + *arg_idx);
		*arg_idx += (cor->op_tab[proc->opcode - 1].dir_size == 0) ? 4
				: cor->op_tab[proc->opcode - 1].dir_size;
	}
	else if (cor->args[i].type == T_IND)
	{
		cor->args[i].val = get_short_arg_value(cor, proc->idx + *arg_idx);
		*arg_idx += 2;
	}
}

/*
** Function that get the values of the arguments necessary for the instruction.
** The types of accepted arguments for the instruction are passed as variadic
** arguments of this function. The function returns true if the types of
** argument are valid, false otherwise.
*/

int					get_args(t_cor *cor, t_proc *proc)
{
	int				arg_idx;
	int				i;
	int				valid_args;

	arg_idx = 2;
	valid_args = true;
	i = -1;
	while (++i < cor->op_tab[proc->opcode - 1].nb_args)
	{
		cor->args[i].type = get_arg_type(cor->arena[restricted_addr(proc->idx
				+ 1)], i);
		get_arg(cor, proc, &arg_idx, i);
		if (!(cor->args[i].type & cor->op_tab[proc->opcode - 1].args[i])
				|| (cor->args[i].type == T_REG && (cor->args[i].val <= 0
						|| cor->args[i].val > REG_NUMBER)))
			valid_args = false;
	}
	proc->move = arg_idx;
	return (valid_args);
}

/*
** Returns the value of a register as an int.
*/

int					get_reg_value(unsigned char *reg)
{
	int		i;
	int		res;

	i = 3;
	res = reg[3];
	while (--i >= 0)
		res = res * 256 + reg[i];
	return (res);
}
