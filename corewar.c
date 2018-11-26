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

int		main(int ac, char **av)
{
	t_vm		vm;
	init(&vm);
	if (ac > 1)
	{
		ft_putstr("count_champs\n");
		count_champs(&vm, ac, av);
		ft_nbrendl(vm.num_champs);
		ft_putstr("load_vm\n");
		load_vm(&vm);
	}
	g_vm = &vm;
	ft_putarena(vm.arena, 64 * 64);
	run_vm(&vm);
}

void	execute_process(t_vm *vm, t_process *cursor)
{
	int		op;


	op = vm->arena[cursor->pc];
	if (cursor->waitcycles)
	{
		cursor->waitcycles--;
		if (cursor->waitcycles == 0)
		{
			op = vm->arena[cursor->start];
			DPRINT("P %4d | ", cursor->n);
			DPRINT("%s ", vm->op_tab[op].name);
			int i = -1;
			while (++i < vm->op_tab[op].nargs)
			{
				if (cursor->is_reg[i])
				{
					DPRINT("r%d ", cursor->params[i] + 1);
				}
				else
				{
					DPRINT("%d ", cursor->params[i]);
				}
			}
			
			//DPRINT("\n");
			g_cw_funcs[op - 1](vm, cursor);
			DPRINT("\n");
			DPRINT("ADV %d ", cursor->pc - cursor->start);
			DPRINT("(0x%04x -> 0x%04x) ", cursor->start, cursor->pc);
			i = cursor->start - 1;
			while (++i < cursor->pc)
				DPRINT("%02x ", vm->arena[MEM(i)]);
			DPRINT("\n");
			cursor->start = cursor->pc;
		}
	}
	else if ((op > 0 && op < 17))
	{
		clear_cursor_params(cursor);
		if (check_args(vm, &vm->op_tab[op], cursor))
		{
			cursor->waitcycles = vm->op_tab[op].cycles;
		} else {
			DPRINT("Skipping faulty arg %s\n", vm->op_tab[op].name);
			cursor->pc++;
		}

	}
	else if (!(op > 0 && op < 17))
	{
		cursor->pc++;
	}
	else
		cursor->pc++;
}

void	run_vm(t_vm	*vm)
{
	char		ch;
	int cyclesgg = 2400000;
	t_process	*cursor;

	if (vm->v == 1)
		init_viz();
	vm->cycle = 1200;
	while (cyclesgg-- && (ch = getch()) == ERR)
	{
		if (vm->v == 1)
			print_vm(vm);
		//usleep(14000);
		cursor = vm->first;
		while (cursor)
		{
			if (!cursor->dead_flag)
				execute_process(vm, cursor);
			//if (cursor->pc < 0)
			//	cursor->pc = MEM_SIZE - (cursor->pc * -1);
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
	ft_putarena(vm->arena, 64 * 64);
	endwin();
}
