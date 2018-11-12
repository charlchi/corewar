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

static void	(*cw_funcs[16])(t_vm *vm, t_process *cursor) = {
	cw_live, cw_ld,   cw_st,   cw_add, 
	cw_sub,  cw_and,  cw_or,   cw_xor,
	cw_zjmp, cw_ldi,  cw_sti,   cw_fork,
	cw_lld,  cw_lldi, cw_lfork, cw_aff
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
	//printf("%p\n", vm.first);
	g_vm = &vm;
	ft_putarena(vm.arena, 64 * 64);
	run_vm(&vm);
}

void	execute_process(t_vm *vm, t_process *cursor)
{
	//printf("exec %d waitcycles %d\n", vm->arena[cursor->pc], cursor->waitcycles);
	int op;

	op = 0;
	while (op < 3)
	{
		cursor->is_reg[op] = 0;
		cursor->params[op] = 0;
		op++;
	}
	op = vm->arena[cursor->pc];
	//if (cursor->waitcycles == 0) printf("%d %d %d %d %d %d %d %d\n",
	//	vm->arena[MEM(cursor->pc+0)],
	//	vm->arena[MEM(cursor->pc+1)],
	//	vm->arena[MEM(cursor->pc+2)],
	//	vm->arena[MEM(cursor->pc+3)],
	//	vm->arena[MEM(cursor->pc+4)],
	//	vm->arena[MEM(cursor->pc+5)],
	//	vm->arena[MEM(cursor->pc+6)],
	//	vm->arena[MEM(cursor->pc+7)]
	//);
	if (cursor->waitcycles)
	{
		cursor->waitcycles--;
	}
	else if ((op > 0 && op < 17)
		&& check_args(vm, &vm->op_tab[op], cursor))
	{
		//printf("\t\t\t\texec [%s] at %d\n", vm->op_tab[op].name, cursor->start);
		cursor->waitcycles = vm->op_tab[op].cycles;
		//printf("going into cw_funcs\n");
		cw_funcs[op - 1](vm, cursor);

	}
	else if (!(op > 0 && op < 17))
	{
		//printf("%d not an op\n", op);
		cursor->pc++;
	}
	else
		cursor->pc++;
}

void	run_vm(t_vm	*vm)
{
	t_process	*cursor;

	initscr();
	//cbreak();
	noecho();
	//nonl();
	clear();
	//intrflush(stdscr, FALSE);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);


	

	int gg;
	int cyclesgg = 1000000;
	
	int i;
	while (cyclesgg--)
	{
		refresh();
		erase();
		i = 0;
		attron(COLOR_PAIR(1));
		while (i < 64 * 64) {
			printw("%02x ", vm->arena[i]);
			i++;
			if (i != 0 && i % 64 == 0)
			{
				printw("%02d ", i);
				printw("\n");
			}
		}
		attroff(COLOR_PAIR(1));

		//printf("gg\n");
		gg = 0;
		cursor = vm->first;
		while (cursor)
		{
			attron(COLOR_PAIR(gg%4));
			mvprintw(cursor->pc / 64, cursor->pc % 64 * 3, "xx ", 255);
			attroff(COLOR_PAIR(gg%4));
			mvprintw(0, 0, "");
			if (!cursor->dead_flag)
			{
				execute_process(vm, cursor);
			}
			if (cursor->pc < 0)
			{
				printf("cursor tooo small abort mission!!!\n\n\n\n");
				cursor->pc = MEM_SIZE - (cursor->pc * -1);
			}
			cursor->pc = cursor->pc % MEM_SIZE;
			cursor = cursor->next;
			gg++;
		}
		//printf("\t\t\t\t\t\t\t\t\t\tncursors %d\n", gg);
		vm->total_cycles++;
		vm->cycle--;
		if (!vm->cycle)
		{
			//kill_cursors(vm);
			if (vm->lives >= NBR_LIVE)
			{
				if (!(vm->cycle_to_die < CYCLE_DELTA))
					vm->cycle_to_die -= CYCLE_DELTA;
			}
			vm->cycle = vm->cycle_to_die;
		}
	}
	endwin();
	//exit_sequence(vm);
}
