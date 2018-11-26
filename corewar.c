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

int gg;

void	execute_process(t_vm *vm, t_process *cursor)
{
	int		op;

	op = 0;
	while (op < 3)
	{
		cursor->is_reg[op] = 0;
		cursor->params[op] = 0;
		op++;
	}
	op = vm->arena[cursor->pc];
	if (cursor->waitcycles)
	{
		cursor->waitcycles--;
	}
	else if ((op > 0 && op < 17))
	{
		if (check_args(vm, &vm->op_tab[op], cursor))
		{
			//printf("P   %d | ", gg);
			cursor->waitcycles = vm->op_tab[op].cycles;
			//printf("%s ", vm->op_tab[op].name);
			//int i = 0;
			//while (i < vm->op_tab[op].nargs)
				//printf("%d ", cursor->params[i++]);
			//printf("\n");
			g_cw_funcs[op - 1](vm, cursor);
		} else {
			//printf("error reading %s\n", vm->op_tab[op].name);
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
	int cyclesgg = 24000;
	t_process	*cursor;

	if (vm->v)
		init_viz();
	vm->cycle = 1200;
	while (cyclesgg--)
	{
		if (vm->v)
			print_vm(vm);
		usleep(2000);
		gg = 1;
		cursor = vm->first;
		while (cursor)
		{
			if (!cursor->dead_flag)
			{
				cursor->start = cursor->pc;
				execute_process(vm, cursor);
			}
			//if (cursor->pc < 0)
			//	cursor->pc = MEM_SIZE - (cursor->pc * -1);
			cursor->pc = cursor->pc % MEM_SIZE;
			cursor = cursor->next;
			gg++;
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
