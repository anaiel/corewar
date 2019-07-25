/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrigalo <dtrigalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:23:19 by anleclab          #+#    #+#             */
/*   Updated: 2019/07/11 14:50:16 by dtrigalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Initializes the opcode and wait time of the new operation after a proc has
** moved.
*/

static void	init_instr(t_cor *cor, t_proc *proc)
{
	proc->opcode = cor->arena[proc->idx];
	if (proc->opcode == 0 || proc->opcode > NB_OPERATIONS)
		proc->wait = 1;
	else
		proc->wait = cor->op_tab[proc->opcode - 1].wait;
}

/*
** Processes execute the instructions they are placed on. Details about the
** instructions can be found in the corresponding files. They have the following
** information:
** - opcode: code the proc sits on, wich represents the instruction to be
**   performed
** - wait: number of cycles the proc has to wait before the instruction is
**   performed
** - argcode: wether or not the instruction is followed by a byte representing
**   the types of arguments that follow (the 2 first bits correspond to the
**   first argument, and so on. 01 represents a REG, 10 a DIR and 11 an IND)
** - args: number and type of arguments required by the instruction
** - addressing restriction: whether or not addresses should be restricted with
**   % IDX_MOD
** - carry: whether or not the instruction modifies the carry of the proc, and
**   if so, how
** - description: what the instruction actually does
*/

static void	execute_process(t_proc *proc, t_cor *cor)
{
	int i;

	if (cor->visual_on)
		cor->visu->attr_arena[proc->idx].cursor = true;
	if (!proc->wait)
		init_instr(cor, proc);
	if (!(--(proc->wait)))
	{
		if (proc->opcode && proc->opcode <= NB_OPERATIONS)
			cor->op_tab[proc->opcode - 1].f(cor, proc);
		else
			proc->move = 1;
		if (cor->verbose & V_PROC && (proc->opcode != 9 || !proc->carry)
				&& proc->opcode && proc->opcode <= NB_OPERATIONS)
		{
			ft_printf("ADV %d (0x%0.4x -> 0x%0.4x) ", proc->move, proc->idx,
					proc->idx + proc->move);
			i = -1;
			while (++i < proc->move)
				ft_printf("%.2x ", cor->arena[restricted_addr(proc->idx + i)]);
			ft_putchar('\n');
		}
		proc->idx = restricted_addr(proc->idx + proc->move);
	}
}

/*
** "Kills" (removes from the list) the processes that have not performed a
** live operation in the last period.
*/

static void	kill_processes(t_cor *cor)
{
	t_proc *current;
	t_proc *previous;

	previous = NULL;
	current = cor->procs;
	while (current)
		if (current->last_live_cycle <= cor->curr_cycle - cor->cycle_to_die
				|| cor->cycle_to_die <= 0)
		{
			if (cor->verbose & V_DEATHS)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
						current->n, cor->curr_cycle - current->last_live_cycle,
						cor->cycle_to_die);
			if (previous && cor->nb_procs--)
				previous->next = current->next;
			else
				cor->procs = current->next;
			delete_proc(&current);
			current = (previous) ? previous->next : cor->procs;
		}
		else
		{
			previous = current;
			current = current->next;
		}
}

static void	end_period(t_cor *cor)
{
	int i;

	kill_processes(cor);
	if (cor->nb_live >= NBR_LIVE || cor->nb_checks >= MAX_CHECKS)
	{
		cor->cycle_to_die -= CYCLE_DELTA;
		if (cor->verbose & V_CYCLES)
			ft_printf("Cycle to die is now %d\n", cor->cycle_to_die);
		cor->nb_checks = 1;
	}
	else
		cor->nb_checks++;
	cor->curr_cycle_period = 0;
	cor->nb_live = 0;
	i = -1;
	while (++i < cor->nb_champs)
	{
		cor->champs[i]->lives_in_last_period = cor->champs[i]
				->lives_in_curr_period;
		cor->champs[i]->lives_in_curr_period = 0;
	}
}

/*
** This is the function that lets the champions fight. The algorithm is as
** follows :
**     As long as there is still a process alive:
**         -> increment the current cycle
**         For every process in the list (see execute_process):
**             -> if it is the begining of the game or the process moved in the
**                last cycle, set the value of the opcode and wait time of the
**                next process (the one on which the cursor stands)
**             -> decrease the wait time
**             -> if the wait time is over, execute the operation and move the
**                cursor
**         If the end of the period was reached or if the period is negative
**         (see end_period):
**             -> if more than NBR_LIVE live operations where performed in the
**                last period, or if MAX_CHECKS periods took place without
**                reducing the period, reduce the period
**         -> dump the memory and exit if the dump option is set and the
**            current cycle is the dump cycle
*/

void		battle(t_cor *cor)
{
	t_proc *cache;

	while ((cache = cor->procs))
	{
		cor->curr_cycle++;
		cor->curr_cycle_period++;
		if (cor->verbose & V_CYCLES)
			ft_printf("It is now cycle %d\n", cor->curr_cycle);
		while (cache)
		{
			execute_process(cache, cor);
			cache = cache->next;
		}
		if (cor->cycle_to_die <= 0
				|| cor->curr_cycle_period == (unsigned int)cor->cycle_to_die)
			end_period(cor);
		if (cor->dump && cor->curr_cycle == cor->dump_cycle)
			dump(cor);
		if (cor->visual_on)
		{
			while (cor->visu->is_running == false)
				manager(cor, wgetch(stdscr));
			apply_speed(cor);
		}
	}
}
