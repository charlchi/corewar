/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 11:42:54 by agabrie           #+#    #+#             */
/*   Updated: 2018/09/21 09:17:48 by mgerber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "corewar.h"

void	init_viz(void)
{
	initscr();
	noecho();
	nodelay(stdscr, TRUE);
	clear();
	start_color();
	use_default_colors();
	init_pair(0, COLOR_WHITE, COLOR_RED);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_GREEN);
}

void	print_arena(t_vm *vm)
{
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
	
}

void	print_cursors(t_vm *vm)
{
	t_process	*c;
	int			x;
	int			y;
	int			i;

	c = vm->first;
	while (c) {
		if (!c->dead_flag) {
			x = 1 + c->start / 64;
			y = 1 + (c->start % 64 * 3);
			//i = c->waitcycles ? c->start : c->pc;
			i = c->start;
			attron(COLOR_PAIR(5));
			mvprintw(x, y, "%02x", vm->arena[i]);
			attroff(COLOR_PAIR(5));
			mvprintw(0, 0, "");
		}
		c = c->next;
	}
}

void	print_info(t_vm *vm)
{
	mvprintw(66, 0, "%8d cycle", vm->cycle);
	mvprintw(67, 0, "%8d total_cycles", vm->total_cycles);
	mvprintw(68, 0, "%8d lives", vm->lives);
	mvprintw(69, 0, "%8d cycle_to_die", vm->cycle_to_die);
}

void	print_vm(t_vm *vm)
{
	refresh();
	erase();
	print_arena(vm);
	print_cursors(vm);
	print_info(vm);
}
