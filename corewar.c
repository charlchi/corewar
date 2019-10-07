/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:06:25 by cmoller           #+#    #+#             */
/*   Updated: 2018/12/04 14:06:27 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "corewar.h"
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KRST "\033[0m"

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
		if (check_args(vm, &vm->op_tab[op], c))
		{
			DPRINT("P %4d | %s ", c->n, vm->op_tab[op].name);
			i = -1;
			while (++i < vm->op_tab[op].nargs)
				c->is_reg[i] ? DPRINT("r%d ", c->params[i] + 1)
				: DPRINT("%d ", c->params[i]);
			g_cw_funcs[op - 1](vm, c);
			DPRINT("\nADV %d ", c->pc - c->start);
			DPRINT("(0x%04x -> 0x%04x) ", c->start, c->pc);
			i = MEM(c->start - 1);
			while (++i < MEM(c->pc))
				DPRINT("%02x ", vm->arena[MEM(i)]);
			DPRINT("\n");
			c->start = c->pc;
		}
	}
}

void		execute_cursors(t_vm *vm)
{
	int			op;
	t_process	*c;

	c = vm->first;
	while (c)
	{
		if (!c->dead_flag)
		{
			op = vm->arena[MEM(c->pc)];
			if (c->waitcycles)
				execute_process(vm, c);
			else if ((op > 0 && op < 17))
				c->waitcycles = vm->op_tab[op].cycles - 1;
			else
				c->pc++;
			c->pc = c->pc % MEM_SIZE;
		}
		c = c->next;
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
	char		*val;

	if (vm->last_livep == -1)
		ft_putstr(KRED "No champion called live!\nNobody wins...\n" KRST);
	else
	{
		ch = vm->champs[vm->last_livep];
		val = ft_itoa(ch.number);
		ft_putstr(KGRN "Contestant ");
		ft_putstr(val);
		ft_putstr(", \"");
		ft_putstr((char *)&ch.prog_name[0]);
		ft_putstr("\", has won !\n" KRST);
		if (val)
			free(val);
	}
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
		execute_cursors(vm);
		check_cursors(vm);
		vm->total_cycles++;
		vm->cycle--;
		if (vm->cycle < 0 || vm->nolive == 1)
			break ;
	}
	if (vm->v == 2)
	{
		endwin();
		usleep(50000);
	}
	if (vm->total_cycles == vm->dump)
		dump_vm(vm);
	else
		print_winner(vm);
	// TODO just put this in a function somewhere so it norms
	t_process	*cc;
	t_process	*prev;
	cc = vm->first;
	while (cc)
	{
		prev = cc;
		cc = cc->next;
		free(prev);
	}
	exit(0);
}
