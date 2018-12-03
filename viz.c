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
	init_pair(0, COLOR_BLACK, COLOR_WHITE);
	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_BLUE);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, COLOR_BLACK, COLOR_CYAN);
	init_pair(9, COLOR_WHITE, COLOR_BLACK);
}

void	print_arena(t_vm *vm)
{
	int			i;

	i = -1;
	while (++i < 64*2 + 2)
		printw(" ");
	printw("\n ");
	i = 0;	
	while (i < 64 * 64) {
		attron(COLOR_PAIR(vm->colors[i]));
		printw("%02x", vm->arena[i]);
		attroff(COLOR_PAIR(vm->colors[i]));
		i++;
		if (i != 0 && i % 64 == 0)
		{
			printw(" \n ");
		}
	}
	i = -1;
	while (++i < 64*2 + 1)
		printw(" ");
	printw("\n");
}

void	print_cursors(t_vm *vm)
{
	t_process	*c;
	int			i;
	int			y;
	int			x;

	c = vm->first;
	while (c) {
		if (!c->dead_flag) {
			y = 1 + MEM(c->start) / 64;
			x = 1 + (MEM(c->start) % 64 * 2);
			i = MEM(c->start);
			i %= MEM_SIZE;
			while (i < 0)
				i += MEM_SIZE;
			attron(A_BOLD);
			attron(COLOR_PAIR(9));
			mvprintw(y, x, "%02x", vm->arena[i]);
			attroff(COLOR_PAIR(9));
			attroff(A_BOLD);
			//mvprintw(0, 0, "");
		}
		c = c->next;
	}
}

void	print_info(t_vm *vm)
{
	int			i;
	int			x;

	x = 3 + 64 * 2;
	attron(A_BOLD);
	i = -1;
	while (++i < vm->num_champs)
	{
		attron(COLOR_PAIR(1 + i));
		attron(A_UNDERLINE);
		mvprintw(i * 4 + 1, x, " Player %4d:               \n", i + 1);
		attroff(A_UNDERLINE);
		mvprintw(i * 4 + 2, x, "        Last live: %8d ", vm->champs[i].last_live);
		mvprintw(i * 4 + 3, x, " Lives this cycle: %8d ", vm->champs[i].lives);
		attroff(COLOR_PAIR(1 + i));
	}
	attron(A_UNDERLINE);
	mvprintw(i * 4 + 4, x, " VM                        \n", vm->cycle);
	attroff(A_UNDERLINE);
	mvprintw(i * 4 + 5, x, "    Current cycle:%8d  \n", vm->cycle);
	mvprintw(i * 4 + 6, x, "     Total cycles:%8d  \n", vm->total_cycles);
	mvprintw(i * 4 + 7, x, " Lives this cycle:%8d  \n", vm->lives);
	mvprintw(i * 4 + 8, x, "     Cycle to die:%8d  \n", vm->cycle_to_die);
	attroff(A_BOLD);
}

void	print_vm(t_vm *vm)
{
	refresh();
	erase();
	print_arena(vm);
	print_info(vm);
	print_cursors(vm);
	//usleep(500);
}