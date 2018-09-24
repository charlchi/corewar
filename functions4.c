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
	int	acb;
	int param1;
	int param2;

	cursor->pc++;
	acb = (int)vm->arena[cursor->pc++];
	if (acb == 0b10010000)
		param1 = consume_param(vm->arena, &cursor->pc, 4);
	else //if (acb == 0b11010000)
		param1 = consume_param(vm->arena, &cursor->pc, 2);
	param2 = consume_param(vm->arena, &cursor->pc, 1);
	cursor->reg[param2] = (cursor->pc + param1) % MEM_SIZE;
}

void	cw_lldi(t_vm *vm, t_process *cursor)
{
	char	acb;
	int		param1;
	int		param2;
	int		param3;
	int		index;

	cursor->pc++;
	acb = vm->arena[cursor->pc++];
	
	if (((acb & 0b00010000) >> 4) == 1)
		param1 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	else //if ((((acb & 0b00100000) >> 4) & 0b10) > 0)
		param1 = consume_param(vm->arena, &cursor->pc, 2);
	if (((acb & 0b00001000) >> 2) == 1)
		param2 = cursor->reg[consume_param(vm->arena, &cursor->pc, 2)];
	else //if (((acb & 0b00000100) >> 2) == 2)
		param2 = consume_param(vm->arena, &cursor->pc, 1);
	param3 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	index = (((cursor->pc + param1) % MEM_SIZE) + param2);
	cursor->reg[param3] =
		uctoi(&vm->arena[(cursor->pc + index) % MEM_SIZE], 4);
}

void	cw_lfork(t_vm *vm, t_process *cursor)
{
	t_process	*newcursor;
	int			param1;

	cursor->pc++;
	param1 = consume_param(vm->arena, &cursor->pc, 4);
	newcursor = clone_cursor(cursor, (cursor->pc - 1 + param1) % MEM_SIZE);
	newcursor->carry = 0;
	add_cursor(vm, newcursor);
}

void	cw_aff(t_vm *vm, t_process *cursor)
{
	int param1;

	cursor->pc++;
	param1 = consume_param(vm->arena, &cursor->pc, 1);
	ft_putchar(cursor->reg[param1] % 256);
}