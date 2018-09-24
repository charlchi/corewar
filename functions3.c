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

#include "libft/libft.h"
#include "corewar.h"

void	cw_zjmp(t_vm *vm, t_process *cursor)
{
	int param1;

	cursor->pc++;
	param1 = consume_param(vm->arena, &cursor->pc, 2);
	if (cursor->carry)
		cursor->pc = (cursor->pc + (param1 % IDX_MOD)) % MEM_SIZE;
}

void	cw_ldi(t_vm *vm, t_process *cursor)
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
	index = (((cursor->pc + (param1 % IDX_MOD)) % MEM_SIZE) + param2);
	cursor->reg[param3] =
		uctoi(&vm->arena[(cursor->pc + (index % IDX_MOD)) % MEM_SIZE], 4);
}

void	cw_sti(t_vm *vm, t_process *cursor)
{
	char	acb;
	int		param1;
	int		param2;
	int		param3;


	cursor->pc++;
	acb = vm->arena[cursor->pc++];
	param1 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	if (((acb & 0b00010000) >> 4) == 1)
		param2 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	else //if ((((acb & 0b00100000) >> 4) & 0b10) > 0)
		param2 = consume_param(vm->arena, &cursor->pc, 2);
	if (((acb & 0b00001000) >> 2) == 1)
		param3 = cursor->reg[consume_param(vm->arena, &cursor->pc, 2)];
	else //if (((acb & 0b00000100) >> 2) == 2)
		param3 = consume_param(vm->arena, &cursor->pc, 1);
	printf("pc %d\n", cursor->pc);
	printf("%d %d %d\n", param1, param2, param3);
	param2 += param3;

	itouc(&vm->arena[param2 % MEM_SIZE], param1);
}

void	cw_fork(t_vm *vm, t_process *cursor)
{
	t_process	*newcursor;
	int			param1;

	cursor->pc++;
	param1 = consume_param(vm->arena, &cursor->pc, 4);
	newcursor = clone_cursor(cursor, cursor->pc - 1 + (param1 % IDX_MOD));
	newcursor->carry = 0;
	add_cursor(vm, newcursor);
}
