/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 13:52:41 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/21 09:10:19 by mgerber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_live(t_vm *vm, t_process *cursor)
{
	int		num;
	int i;

	i = 0;
	while (i < vm->num_champs)
	{
		if (vm->champs[i].number == cursor->params[0])
		{
			vm->champs[i].lives++;
			vm->lives++;
			vm->champs[i].last_live = vm->total_cycles; 
		}
		i++;
	}
	cursor->live_flag = 1;
}

void	cw_ld(t_vm *vm, t_process *cursor)
{
	int				index;
	int				reg;


	reg = cursor->params[1];
	index = MEM(cursor->start + 2 + (cursor->params[0] % IDX_MOD));
	cursor->reg[reg] = vm->arena[MEM(index + 3)] << 0;
	cursor->reg[reg] += (vm->arena[MEM(index + 2)] << 8);
	cursor->reg[reg] += (vm->arena[MEM(index + 1)] << 16);
	cursor->reg[reg] += (vm->arena[MEM(index + 0)] << 24);
	cursor->carry = !(cursor->reg[reg]);
}

void	cw_st(t_vm *vm, t_process *cursor)
{
	int				index;
	int				reg;

	reg = cursor->reg[cursor->params[0]];
	if (cursor->is_reg[1])
		cursor->reg[cursor->params[1]] = reg;
	else
	{
		index = (cursor->start + 2 + (cursor->params[1] % IDX_MOD));
		vm->arena[MEM(index + 0)] = (reg & 0xff000000) >> 24;
		vm->arena[MEM(index + 1)] = (reg & 0x00ff0000) >> 16;
		vm->arena[MEM(index + 2)] = (reg & 0x0000ff00) >> 8;
		vm->arena[MEM(index + 3)] = (reg & 0x000000ff) >> 0;
		vm->colors[MEM(index + 0)] = vm->colors[MEM(cursor->start)];
		vm->colors[MEM(index + 1)] = vm->colors[MEM(cursor->start)];
		vm->colors[MEM(index + 2)] = vm->colors[MEM(cursor->start)];
		vm->colors[MEM(index + 3)] = vm->colors[MEM(cursor->start)];
	}
}

void	cw_add(t_vm *vm, t_process *cursor)
{
	int			r1;
	int			r2;
	int			r3;
	
	r1 = cursor->params[0];
	r2 = cursor->params[1];
	r3 = cursor->params[2];
	cursor->reg[r3] = cursor->reg[r1] + cursor->reg[r2];
	cursor->carry = !(cursor->reg[r3]);
}
