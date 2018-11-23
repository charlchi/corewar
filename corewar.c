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
	else if ((op > 0 && op < 17)
		&& check_args(vm, &vm->op_tab[op], cursor))
	{
		cursor->waitcycles = vm->op_tab[op].cycles;
		//fprintf(stderr, "%s ", vm->op_tab[op].name);
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
	noecho();
	clear();
	start_color();
	use_default_colors();
	init_pair(0, COLOR_WHITE, COLOR_RED);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_GREEN);

	int gg;
	int cyclesgg = 1000000;
	
	while (cyclesgg--)
	{
		refresh();
		erase();
		print_vm(vm);
		mvprintw(66, 0, "%10d cycle", vm->cycle);
		mvprintw(67, 0, "%10d total_cycles", vm->total_cycles);
		mvprintw(68, 0, "%10d lives", vm->lives);
		mvprintw(69, 0, "%10d cycle_to_die", vm->cycle_to_die);
		usleep(2000);
		gg = 0;
		cursor = vm->first;
		while (cursor)
		{
			if (!cursor->dead_flag)
				execute_process(vm, cursor);
			if (cursor->pc < 0)
				cursor->pc = MEM_SIZE - (cursor->pc * -1);
			cursor->pc = cursor->pc % MEM_SIZE;
			cursor = cursor->next;
			gg++;
		}
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
		vm->total_cycles++;
		vm->cycle--;
		
	}
	endwin();
	//exit_sequence(vm);
}

void	print_vm(t_vm *vm)
{
	t_process	*cursor;
	int			i;

	i = 0;
	printw("\n");
	while (i < 64 * 64) {
		printw(" ");
		attron(COLOR_PAIR(vm->colors[i]));
		printw("%02x", vm->arena[i]);
		attroff(COLOR_PAIR(vm->colors[i]));
		i++;
		if (i != 0 && i % 64 == 0)
		{
			printw(" %02", i);
			printw("\n");
		}
	}
	cursor = vm->first;
	while (cursor)
	{
		attron(COLOR_PAIR(5));
		mvprintw(cursor->pc / 64, 1 + (cursor->pc % 64 * 3), "%02x", vm->arena[i]);
		attroff(COLOR_PAIR(5));
		mvprintw(0, 0, "");
		cursor = cursor->next;
	}
}


