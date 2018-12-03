/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:58:07 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/24 16:58:09 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_zjmp(t_vm *vm, t_process *c)
{
	int			index;

	(void)vm;
	index = MEM(c->start + (c->params[0] % IDX_MOD));
	if (c->carry)
	{
		DPRINT("OK");
		c->pc = index;
		c->start = index;
	}
}

void	cw_ldi(t_vm *vm, t_process *c)
{
	int			index;
	int			reg;

	if (c->is_reg[0])
		c->params[0] = c->reg[c->params[0]];
	if (c->is_reg[1])
		c->params[1] = c->reg[c->params[1]];
	reg = c->params[2];
	index = MEM((c->start + ((c->params[0] + c->params[1]) % IDX_MOD)));
	index %= MEM_SIZE;
	while (index < 0)
		index += MEM_SIZE;
	DPRINT("\n       | -> load");
	c->reg[reg] = 0;
	c->reg[reg] += (vm->arena[MEM(index + 3)]) << 0;
	c->reg[reg] += (vm->arena[MEM(index + 2)]) << 8;
	c->reg[reg] += (vm->arena[MEM(index + 1)]) << 16;
	c->reg[reg] += (vm->arena[MEM(index + 0)]) << 24;
	c->carry = !(c->reg[reg]);
}

void	cw_sti(t_vm *vm, t_process *c)
{
	int				index;
	int				reg;

	reg = c->reg[c->params[0]];
	if (c->is_reg[1])
		c->params[1] = c->reg[c->params[1]];
	if (c->is_reg[2])
		c->params[2] = c->reg[c->params[2]];
	index = (c->params[1] + c->params[2]) % IDX_MOD;
	index = MEM(c->start + index);
	index %= MEM_SIZE;
	while (index < 0)
		index += MEM_SIZE;
	DPRINT("\n       | -> store acb[%02x] ", vm->arena[MEM(c->start + 1)]);
	vm->arena[MEM(index + 3)] = ((reg & 0xff000000) >> 24);
	vm->arena[MEM(index + 2)] = ((reg & 0x00ff0000) >> 16);
	vm->arena[MEM(index + 1)] = ((reg & 0x0000ff00) >> 8);
	vm->arena[MEM(index + 0)] = ((reg & 0x000000ff) >> 0);
	vm->colors[MEM(index + 3)] = vm->colors[MEM(c->start)];
	vm->colors[MEM(index + 2)] = vm->colors[MEM(c->start)];
	vm->colors[MEM(index + 1)] = vm->colors[MEM(c->start)];
	vm->colors[MEM(index + 0)] = vm->colors[MEM(c->start)];
}

void	cw_fork(t_vm *vm, t_process *c)
{
	int				index;
	t_process		*newc;

	index = MEM(c->start + (c->params[0] % IDX_MOD));
	index %= MEM_SIZE;
	while (index < 0)
		index += MEM_SIZE;
	DPRINT("(%d) ", index);
	newc = clone_cursor(c, index);
	newc->carry = c->carry;
	add_cursor(vm, newc);
}
