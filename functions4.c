/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:58:14 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/24 16:58:15 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_lld(t_vm *vm, t_process *cursor)
{
	int				index;
	int				reg;

	reg = cursor->params[1];
	index = MEM(cursor->start + 2 + (cursor->params[0]));
	cursor->reg[reg] = vm->arena[MEM(index + 3) << 0];
	cursor->reg[reg] += (vm->arena[MEM(index + 2)] << 8);
	cursor->reg[reg] += (vm->arena[MEM(index + 1)] << 16);
	cursor->reg[reg] += (vm->arena[MEM(index + 0)] << 24);
	cursor->carry = !(cursor->reg[reg]);
}

void	cw_lldi(t_vm *vm, t_process *cursor)
{
	int			index;
	int			reg;

	if (cursor->is_reg[0])
		cursor->params[0] = cursor->reg[cursor->params[0]];
	if (cursor->is_reg[1])
		cursor->params[1] = cursor->reg[cursor->params[1]];
	reg = cursor->params[2];
	index = MEM(cursor->start + 2 + (cursor->params[0] + cursor->params[1]));
	index %= MEM_SIZE;
	while (index < 0)
		index += MEM_SIZE;
	cursor->reg[reg] = (vm->arena[MEM(index + 3)] << 0);
	cursor->reg[reg] += (vm->arena[MEM(index + 2)] << 8);
	cursor->reg[reg] += (vm->arena[MEM(index + 1)] << 16);
	cursor->reg[reg] += (vm->arena[MEM(index + 0)] << 24);
	cursor->carry = !(cursor->reg[reg]);
}

void	cw_lfork(t_vm *vm, t_process *cursor)
{
	int				index;
	t_process		*newcursor;

	index = MEM(cursor->start + (cursor->params[0]));
	newcursor = clone_cursor(cursor, index);
	add_cursor(vm, newcursor);
}

void	cw_aff(t_vm *vm, t_process *cursor)
{
	(void)vm;
	DPRINT("%c", cursor->reg[cursor->params[0]] % 256);
}
