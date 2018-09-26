/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 09:17:38 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/21 09:17:48 by mgerber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	(*cw_funcs[16])(t_vm *vm, t_process *cursor, int start) = {
	cw_live, cw_ld,   cw_st,   cw_add, 
	cw_sub,  cw_and,  cw_or,   cw_xor,
	cw_zjmp, cw_ldi,  cw_sti,   cw_fork,
	cw_lld,  cw_lldi, cw_lfork, cw_aff
};

void	add_cursor(t_vm *vm, t_process *cursor)
{
	t_process		*curr;
	
	if (vm->first == NULL)
	{
		vm->first = cursor;
	}
	else
	{
		curr = vm->first;
		while (curr->next)
			curr = curr->next;
		curr->next = cursor;
	}
}

/*
int		living_cursors(t_vm *vm)
{
	t_process *cursors;
	int i;

	cursors = vm->first;
	i = 0;
	while (cursors)
	{
		if (cursors->live_flag)
			i = 1;
		cursors->live_flag = 0;
		cursors = cursors->next;
	}
	return (i);
}*/

void	kill_cursors(t_vm *vm)
{
	t_process	*cursors;

	cursors = vm->first;
	while (cursors)
	{
		cursors->dead_flag = !cursors->live_flag;
		cursors = cursors->next;
	}
}

void	execute_process(t_vm *vm, t_process *cursor)
{
	int k;
	if (cursor->waitcycles)
	{
		cursor->waitcycles--;
		return ;
	}
	k = is_action(vm, vm->arena[cursor->pc]);
	if (k)
	{
		printf("----------------executing at %d: %s\n", cursor->pc, vm->op_tab[k - 1].name);
		if (cursor->pc < 0)
			exit(0);
		cw_funcs[k - 1](vm, cursor, cursor->pc);
		printf("^^^^^^^^^^^^^^^^done, now at %d: %s\n", cursor->pc, vm->op_tab[k - 1].name);
		if (cursor->pc < 0)
			exit(0);
	}
	if (!is_action(vm, vm->arena[cursor->pc]))
	{
		cursor->pc++;
		return ;
	}
	cursor->waitcycles = vm->op_tab[vm->arena[cursor->pc] - 1].cycles;
	if (cursor->waitcycles > 1000)
		exit(0);
}












