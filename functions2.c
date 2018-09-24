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

#include "libft/libft.h"
#include "corewar.h"

void	cw_sub(t_vm *vm, t_process *cursor)
{
	int				param1;
	int				param2;

	cursor->pc++;
	param1 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	param2 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	cursor->reg[consume_param(vm->arena, &cursor->pc, 1)] = param1 - param2;
}

void	cw_and(t_vm *vm, t_process *cursor)
{
	unsigned char	acb;
	int				param1;
	int				param2;

	cursor->pc++;
	acb = vm->arena[cursor->pc++];
	if (acb == 0b01110100 || acb == 0b01100100 || acb == 0b01010100)
		param1 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	else // if (acb == 0b11110100 || acb == 0b11100100 || acb == 0b11010100 ||
	//acb == 0b10110100 || acb == 0b10100100 || acb == 0b10010100)
		param1 = cursor->reg[consume_param(vm->arena, &cursor->pc, 2)];
	if (acb == 0b01010100 || acb == 0b10010100 || acb == 0b11010100)
		param2 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	else //if (acb == 0b01110100 || acb == 0b10110100 || acb == 0b11110100 ||
	//acb == 0b01100100 || acb == 0b10100100 || acb == 0b11100100)
		param2 = cursor->reg[consume_param(vm->arena, &cursor->pc, 2)];
	cursor->reg[consume_param(vm->arena, &cursor->pc, 1)] = param1 & param2;
}

void	cw_or(t_vm *vm, t_process *cursor)
{
	unsigned char	acb;
	int				param1;
	int				param2;

	cursor->pc++;
	acb = vm->arena[cursor->pc++];
	if (acb == 0b01110100 || acb == 0b01100100 || acb == 0b01010100)
		param1 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	else //if (acb == 0b11110100 || acb == 0b11100100 || acb == 0b11010100 ||
	//acb == 0b10110100 || acb == 0b10100100 || acb == 0b10010100)
		param1 = cursor->reg[consume_param(vm->arena, &cursor->pc, 2)];
	if (acb == 0b01010100 || acb == 0b10010100 || acb == 0b11010100)
		param2 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	else // if (acb == 0b01110100 || acb == 0b10110100 || acb == 0b11110100 ||
	//acb == 0b01100100 || acb == 0b10100100 || acb == 0b11100100)
		param2 = cursor->reg[consume_param(vm->arena, &cursor->pc, 2)];
	cursor->reg[consume_param(vm->arena, &cursor->pc, 1)] = param1 | param2;
}

void	cw_xor(t_vm *vm, t_process *cursor)
{
	unsigned char	acb;
	int				param1;
	int				param2;

	cursor->pc++;
	acb = vm->arena[cursor->pc++];
	if (acb == 0b01110100 || acb == 0b01100100 || acb == 0b01010100)
		param1 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	else // if (acb == 0b11110100 || acb == 0b11100100 || acb == 0b11010100 ||
	//acb == 0b10110100 || acb == 0b10100100 || acb == 0b10010100)
		param1 = cursor->reg[consume_param(vm->arena, &cursor->pc, 2)];
	if (acb == 0b01010100 || acb == 0b10010100 || acb == 0b11010100)
		param2 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	else //if (acb == 0b01110100 || acb == 0b10110100 || acb == 0b11110100 ||
	//acb == 0b01100100 || acb == 0b10100100 || acb == 0b11100100)
		param2 = cursor->reg[consume_param(vm->arena, &cursor->pc, 2)];
	cursor->reg[consume_param(vm->arena, &cursor->pc, 1)] = param1 ^ param2;
}
