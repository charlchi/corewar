/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:53:42 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/24 16:53:44 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			add_cursor(t_vm *vm, t_process *new)
{
	t_process	*curr;

	if (vm->first == NULL)
	{
		new->n = 1;
		vm->first = new;
	}
	else
	{
		curr = vm->first;
		vm->first = new;
		vm->first->n = curr->n + 1;
		vm->first->next = curr;
	}
}

t_process		*create_cursor(int i)
{
	int			k;
	t_process	*newcursor;

	newcursor = malloc(sizeof(t_process));
	if (newcursor == NULL)
		return (NULL);
	newcursor->waitcycles = 0;
	newcursor->live_flag = 0;
	newcursor->dead_flag = 0;
	newcursor->pc = i;
	newcursor->start = i;
	newcursor->carry = 0;
	newcursor->next = NULL;
	k = -1;
	while (++k < REG_NUMBER)
		newcursor->reg[k] = 0;
	return (newcursor);
}

t_process		*clone_cursor(t_process *orig, int pc)
{
	int			k;
	t_process	*clone;

	clone = malloc(sizeof(t_process));
	clone->waitcycles = orig->waitcycles;
	clone->live_flag = orig->live_flag;
	clone->dead_flag = orig->dead_flag;
	clone->carry = orig->carry;
	clone->pc = pc;
	clone->start = pc;
	k = -1;
	while (++k < REG_NUMBER)
		clone->reg[k] = orig->reg[k];
	clone->next = NULL;
	return (clone);
}

void			clear_cursor_params(t_process *cursor)
{
	int			op;

	op = 0;
	while (op < 3)
	{
		cursor->is_reg[op] = 0;
		cursor->params[op] = 0;
		op++;
	}
}

void			kill_cursors(t_vm *vm)
{
	t_process	*cursor;
	int			dead;
	int			total;
	int			i;

	dead = 0;
	total = 0;
	cursor = vm->first;
	while (cursor)
	{
		if (cursor->live_flag == 0)
			cursor->dead_flag = 1;
		if (cursor->dead_flag == 1)
			dead++;
		total++;
		cursor->live_flag = 0;
		cursor = cursor->next;
	}
	if (dead == total)
		vm->nolive = 1;
	i = -1;
	while (++i < vm->num_champs)
		vm->champs[i].lives = 0;
}
