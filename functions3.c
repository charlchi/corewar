/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 13:52:41 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/21 09:19:50 by mgerber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_zjmp(t_vm *vm, t_process *cursor)
{
	int			index;

	if (cursor->carry)
	{
		//printf("params[0] = %d\n", cursor->params[0]);
		//printf("zjmp to %d\n", MEM(cursor->start + (cursor->params[0])));
		cursor->pc = MEM(cursor->start + (cursor->params[0]));
	}
}

void	cw_ldi(t_vm *vm, t_process *cursor)
{
	int			index;
	int			s;
	int			reg;

	if (cursor->is_reg[0])
		cursor->params[0] = cursor->reg[cursor->params[0]];
	if (cursor->is_reg[1])
		cursor->params[1] = cursor->reg[cursor->params[1]];
	reg = cursor->params[2];
	index = (cursor->params[0] + cursor->params[1]);
	index = MEM(cursor->start + (index % IDX_MOD));
	cursor->reg[reg] = vm->arena[MEM(index + 3) << 0];
	cursor->reg[reg] += (vm->arena[MEM(index + 2)] << 8);
	cursor->reg[reg] += (vm->arena[MEM(index + 1)] << 16);
	cursor->reg[reg] += (vm->arena[MEM(index + 0)] << 24);
	cursor->carry = (cursor->reg[reg] == 0);
}

void	cw_sti(t_vm *vm, t_process *cursor)
{
	int				index;
	int				reg;

	reg = cursor->reg[cursor->params[0]];
	if (cursor->is_reg[1])
		cursor->params[1] = cursor->reg[cursor->params[1]];
	if (cursor->is_reg[2])
		cursor->params[2] = cursor->reg[cursor->params[2]];
	index = cursor->start + (cursor->params[1] + cursor->params[2]);
	vm->arena[MEM(index + 0)] = ((reg & 0xff000000) >> 24);
	vm->arena[MEM(index + 1)] = ((reg & 0x00ff0000) >> 16);
	vm->arena[MEM(index + 2)] = ((reg & 0x0000ff00) >> 8);
	vm->arena[MEM(index + 3)] = ((reg & 0x000000ff) >> 0);
	vm->colors[MEM(index + 0)] = vm->colors[MEM(cursor->start)];
	vm->colors[MEM(index + 1)] = vm->colors[MEM(cursor->start)];
	vm->colors[MEM(index + 2)] = vm->colors[MEM(cursor->start)];
	vm->colors[MEM(index + 3)] = vm->colors[MEM(cursor->start)];
}

void	cw_fork(t_vm *vm, t_process *cursor)
{
	int				index;
	t_process		*newcursor;

	index = MEM(cursor->start + (cursor->params[0] % IDX_MOD));
	newcursor = clone_cursor(cursor, index);
	newcursor->carry = 0;
	add_cursor(vm, newcursor);
}
