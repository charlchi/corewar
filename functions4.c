/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 09:00:46 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/21 09:10:19 by mgerber          ###   ########.fr       */
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
	int			s;
	int			reg;

	if (cursor->is_reg[0])
		cursor->params[0] = cursor->reg[cursor->params[0]];
	if (cursor->is_reg[1])
		cursor->params[1] = cursor->reg[cursor->params[1]];
	reg = cursor->reg[cursor->params[2]];
	index = MEM(cursor->start + 2 + (cursor->params[0] + cursor->params[1]));
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
	printf("%c", cursor->reg[cursor->params[0]] % 256);
}