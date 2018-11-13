/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 13:52:41 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/21 09:10:19 by mgerber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_sub(t_vm *vm, t_process *cursor)
{
	int			r1;
	int			r2;
	int			r3;
	
	r1 = cursor->params[0];
	r2 = cursor->params[1];
	r3 = cursor->params[2];
	cursor->reg[r3] = cursor->reg[r1] - cursor->reg[r2];
	cursor->carry = (cursor->reg[r3] == 0);
}

void	cw_and(t_vm *vm, t_process *cursor)
{
	int			reg;

	reg = cursor->params[2];
	if (cursor->is_reg[0])
		cursor->params[0] = cursor->reg[cursor->params[0]];
	if (cursor->is_reg[1])
		cursor->params[1] = cursor->reg[cursor->params[1]];
	cursor->reg[reg] = cursor->params[1] & cursor->params[1];
	cursor->carry = (cursor->reg[reg] == 0);
}

void	cw_or(t_vm *vm, t_process *cursor)
{
	int			reg;
	
	reg = cursor->params[2];
	if (cursor->is_reg[0])
		cursor->params[0] = cursor->reg[cursor->params[0]];
	if (cursor->is_reg[1])
		cursor->params[1] = cursor->reg[cursor->params[1]];
	cursor->reg[reg] = cursor->params[1] | cursor->params[1];
	cursor->carry = (cursor->reg[reg] == 0);
}

void	cw_xor(t_vm *vm, t_process *cursor)
{
	int			reg;

	reg = cursor->params[2];
	if (cursor->is_reg[0])
		cursor->params[0] = cursor->reg[cursor->params[0]];
	if (cursor->is_reg[1])
		cursor->params[1] = cursor->reg[cursor->params[1]];
	cursor->reg[reg] = cursor->params[1] ^ cursor->params[1];
	cursor->carry = (cursor->reg[reg] == 0);
}
