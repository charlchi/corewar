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

void			add_cursor(t_vm *vm, t_process *cursor)
{
	t_process	*curr;

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
	k = -1;
	while (++k < REG_NUMBER)
		clone->reg[k] = orig->reg[k];
	clone->next = NULL;
	return (clone);
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
}
*/

void			kill_cursors(t_vm *vm)
{
	t_process	*cursors;

	cursors = vm->first;
	while (cursors)
	{
		cursors->dead_flag = !cursors->live_flag;
		cursors = cursors->next;
	}
}
