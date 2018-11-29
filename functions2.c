/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:58:00 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/24 16:58:02 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_sub(t_vm *vm, t_process *cursor)
{
	int			r1;
	int			r2;
	int			r3;

	(void)vm;
	r1 = cursor->params[0];
	r2 = cursor->params[1];
	r3 = cursor->params[2];
	cursor->reg[r3] = cursor->reg[r1] - cursor->reg[r2];
	cursor->carry = !(cursor->reg[r3]);
}

void	cw_and(t_vm *vm, t_process *cursor)
{
	int			reg;

	(void)vm;
	reg = cursor->params[2];
	if (cursor->is_reg[0])
		cursor->params[0] = cursor->reg[cursor->params[0]];
	if (cursor->is_reg[1])
		cursor->params[1] = cursor->reg[cursor->params[1]];
	cursor->reg[reg] = cursor->params[0] & cursor->params[1];
	cursor->carry = !(cursor->reg[reg]);
}

void	cw_or(t_vm *vm, t_process *cursor)
{
	int			reg;

	(void)vm;
	reg = cursor->params[2];
	if (cursor->is_reg[0])
		cursor->params[0] = cursor->reg[cursor->params[0]];
	if (cursor->is_reg[1])
		cursor->params[1] = cursor->reg[cursor->params[1]];
	cursor->reg[reg] = cursor->params[0] | cursor->params[1];
	cursor->carry = !(cursor->reg[reg]);
}

void	cw_xor(t_vm *vm, t_process *cursor)
{
	int			reg;

	(void)vm;
	reg = cursor->params[2];
	if (cursor->is_reg[0])
		cursor->params[0] = cursor->reg[cursor->params[0]];
	if (cursor->is_reg[1])
		cursor->params[1] = cursor->reg[cursor->params[1]];
	cursor->reg[reg] = cursor->params[0] ^ cursor->params[1];
	cursor->carry = !(cursor->reg[reg]);
}
