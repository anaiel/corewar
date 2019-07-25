/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/07/03 17:44:16 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

struct s_op	op_tab[NB_OPERATIONS + 1] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", &instr_live, 4, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5,
		"load", &instr_ld, 4, 4},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5,
		"store", &instr_st, 0, 2},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10,
		"addition", &instr_add, 0, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10,
		"soustraction", &instr_sub, 0, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", &instr_and, 4, 4},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", &instr_or, 4, 4},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", &instr_xor, 4, 4},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", &instr_zjmp, 2, 0},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", &instr_ldi, 2, 4},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", &instr_sti, 2, 4},
	{"fork", 1, {T_DIR}, 12, 800, "fork", &instr_fork, 2, 0},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10,
		"long load", &instr_lld, 4, 4},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", &instr_lldi, 2, 4},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", &instr_lfork, 2, 0},
	{"aff", 1, {T_REG}, 16, 2, "aff", &instr_aff, 0, 0},
	{0, 0, {0}, 0, 0, 0, NULL, 0, 0}
};
