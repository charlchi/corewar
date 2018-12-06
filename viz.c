/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:06:07 by cmoller           #+#    #+#             */
/*   Updated: 2018/12/04 14:06:11 by cmoller          ###   ########.fr       */
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
	while (++i < 64 * 2 + 2)
		printw(" ");
	printw("\n ");
	i = 0;
	while (i < 64 * 64)
	{
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
	while (++i < 64 * 2 + 1)
		printw(" ");
	printw("\n");
}

void	print_cursors(t_vm *vm)
{
	t_process	*c;
	int			i;
	int			x;

	c = vm->first;
	while (c)
	{
		if (!c->dead_flag)
		{
			x = 1 + (MEM(c->start) % 64 * 2);
			i = MEM(c->start);
			attron(A_BOLD);
			attron(COLOR_PAIR(9));
			if (vm->arena[i] == 0 && !c->waitcycles)
				mvprintw(1 + MEM(c->pc) / 64, 1 + (MEM(c->pc) % 64 * 2),
					"%02x", vm->arena[i]);
			else
				mvprintw(1 + MEM(c->start) / 64, x, "%02x", vm->arena[i]);
			attroff(COLOR_PAIR(9));
			attroff(A_BOLD);
		}
		c = c->next;
	}
}

void	print_info(t_vm *vm)
{
	int			i;
	int			x;

	x = 3 + 64 * 2;
	i = -1;
	while (++i < vm->num_champs)
	{
		attron(COLOR_PAIR(1 + i));
		attron(A_UNDERLINE);
		mvprintw(i * 4 + 1, x, " %-16s #%-9d\n",
			vm->champs[i].prog_name, vm->champs[i].number);
		attroff(A_UNDERLINE);
		mvprintw(i * 4 + 2, x, "        Last live: %8d ",
			vm->champs[i].last_live);
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
	mvprintw(i * 4 + 9, x, "           Checks:%8d  \n", vm->checks);
}

void	print_vm(t_vm *vm)
{
	refresh();
	erase();
	print_arena(vm);
	print_info(vm);
	print_cursors(vm);
	usleep(100);
}
