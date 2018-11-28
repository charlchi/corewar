/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 11:42:54 by agabrie           #+#    #+#             */
/*   Updated: 2018/09/21 09:17:48 by mgerber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "corewar.h"

t_vm	*g_vm;

static void	(*g_cw_funcs[16])(t_vm *vm, t_process *cursor) = {
	cw_live, cw_ld, cw_st, cw_add,
	cw_sub, cw_and, cw_or, cw_xor,
	cw_zjmp, cw_ldi, cw_sti, cw_fork,
	cw_lld, cw_lldi, cw_lfork, cw_aff
};

void	execute_process(t_vm *vm, t_process *c)
{
	int		op;


	op = vm->arena[c->pc];
	if (c->waitcycles)
	{
		c->waitcycles--;
		if (c->waitcycles == 0)
		{
			op = vm->arena[c->start];
			DPRINT("P %4d | ", c->n);
			DPRINT("%s ", vm->op_tab[op].name);
			int i = -1;
			while (++i < vm->op_tab[op].nargs)
				c->is_reg[i] ? DPRINT("r%d ", c->params[i] + 1)
				: DPRINT("%d ", c->params[i]);
			
			//DPRINT("\n");
			g_cw_funcs[op - 1](vm, c);
			DPRINT("\n");
			DPRINT("ADV %d ", c->pc - c->start);
			DPRINT("(0x%04x -> 0x%04x) ", c->start, c->pc);
			i = c->start - 1;
			while (++i < c->pc)
				DPRINT("%02x ", vm->arena[MEM(i)]);
			DPRINT("\n");
			c->start = c->pc;
		}
	}
	else if ((op > 0 && op < 17))
	{
		clear_cursor_params(c);
		if (check_args(vm, &vm->op_tab[op], c))
		{
			c->waitcycles = vm->op_tab[op].cycles;
		} else {
			DPRINT("Skipping faulty arg %s\n", vm->op_tab[op].name);
			c->pc++;
		}
	}
	else
		c->pc++;
}

void	run_vm(t_vm	*vm)
{
	char		ch;
	int cyclesgg = 24000;
	t_process	*cursor;

	if (vm->v == 1)
		init_viz();
	vm->cycle = 1200;
	while (cyclesgg-- && !((ch = getch()) >= 'a' && ch <= 'z'))
	{
		if (vm->v == 1)
			print_vm(vm);
		usleep(2000);
		cursor = vm->first;
		while (cursor)
		{
			if (!cursor->dead_flag)
				execute_process(vm, cursor);
			cursor->pc = cursor->pc % MEM_SIZE;
			cursor = cursor->next;
		}
		if (!vm->cycle)
		{
			if (vm->lives >= NBR_LIVE)
			{
				if (!(vm->cycle_to_die < CYCLE_DELTA))
					vm->cycle_to_die -= CYCLE_DELTA;
			}
			vm->cycle = vm->cycle_to_die;
			kill_cursors(vm);
		}
		vm->total_cycles++;
		vm->cycle--;
		
	}
	endwin();
}
