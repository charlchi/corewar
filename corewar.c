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

static		void(*g_cw_funcs[16])(t_vm *vm, t_process *cursor) = {
	cw_live,
	cw_ld,
	cw_st,
	cw_add,
	cw_sub,
	cw_and,
	cw_or,
	cw_xor,
	cw_zjmp,
	cw_ldi,
	cw_sti,
	cw_fork,
	cw_lld,
	cw_lldi,
	cw_lfork,
	cw_aff
};

void		execute_process(t_vm *vm, t_process *c)
{
	int			op;
	int			i;

	c->waitcycles--;
	op = vm->arena[MEM(c->pc)];
	if (c->waitcycles == 0 && (op > 0 && op < 17))
	{
		clear_cursor_params(c);
		check_args(vm, &vm->op_tab[op], c);
		DPRINT("P %4d | ", c->n);
		DPRINT("%s ", vm->op_tab[op].name);
		i = -1;
		while (++i < vm->op_tab[op].nargs)
			c->is_reg[i] ? DPRINT("r%d ", c->params[i] + 1)
			: DPRINT("%d ", c->params[i]);
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

void		execute_cursors(t_vm *vm)
{
	int			op;
	t_process	*c;

	c = vm->first;
	while (c)
	{
		DPRINT("ff\n");
		if (!c->dead_flag)
		{
			DPRINT("%d\n", MEM(c->pc));
			op = vm->arena[MEM(c->pc)];
			DPRINT("op %d\n", op);
			if (c->waitcycles)
				execute_process(vm, c);
			else if ((op > 0 && op < 17))
				c->waitcycles = vm->op_tab[op].cycles - 1;
			else
				c->pc++;
			c->pc = c->pc % MEM_SIZE;
		}
		c = c->next;
		DPRINT("gg\n");
	}
	
}

void		check_cursors(t_vm *vm)
{
	if (!vm->cycle)
	{
		vm->checks++;
		if (vm->lives >= NBR_LIVE || vm->checks == 10)
		{
			if (!(vm->cycle_to_die < CYCLE_DELTA) || vm->checks == 10)
			{
				vm->checks = 0;
				vm->cycle_to_die -= CYCLE_DELTA;
				vm->lives = 0;
			}
		}
		vm->cycle = vm->cycle_to_die;
		kill_cursors(vm);
	}
}

void		print_winner(t_vm *vm)
{
	t_champ		ch;

	ch = vm->champs[vm->last_livep];
	ft_putstr("Contestant ");
	ft_putstr(ft_itoa(ch.number));
	ft_putstr(", \"");
	ft_putstr((char *)&ch.prog_name[0]);
	ft_putstr("\", has won !\n");
}

void		run_vm(t_vm *vm)
{
	char		c;

	if (vm->v == 2)
		init_viz();
	while (vm->total_cycles != vm->dump && !((c = getch()) >= 'a' && c <= 'z'))
	{
		if (vm->v == 2)
			print_vm(vm);
		DPRINT("executing\n");
		execute_cursors(vm);
		DPRINT("done, checking\n");
		check_cursors(vm);
		DPRINT("done\n");
		vm->total_cycles++;
		vm->cycle--;
		if (vm->cycle < 0 || vm->nolive == 1)
			break ;
		DPRINT("1cycle\n");
	}
	DPRINT("Game Ended\n");
	if (vm->v == 2)
	{
		endwin();
		usleep(50000);
	}
	if (vm->total_cycles == vm->dump)
		dump_vm(vm);
	else
		print_winner(vm);
	exit(0);
}

void		dump_vm(t_vm *vm)
{
	int			i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i != 0 && i % 64 == 0)
			printf("\n");
		if (i % 64 == 0)
			printf("0x%04x : ", i);
		printf("%02x", vm->arena[i]);
		i++;
	}
	printf("\n");
}
