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

#include "libft/libft.h"
#include "corewar.h"

void	cw_live(t_vm *vm, t_process *cursor)
{
	int i;

	i = 0;
	while (i < vm->num_champs)
	{
		if (uctoi(vm->champs[i].number, 4) == uctoi(vm->arena + cursor->pc, 4))
		{
			vm->champs[i].lives++;
			vm->champs[i].last_live = vm->total_cycles;
		}
		i++;
	}
	cursor->live_flag = 1;
	cursor->pc += 5;
}

void	cw_ld(t_vm *vm, t_process *cursor)
{
	unsigned char	acb;
	int				param1;
	int				param2;

	cursor->pc++;
	acb = vm->arena[cursor->pc++];
	if (acb == 0b10010000)
		param1 = consume_param(vm->arena, &cursor->pc, 4);
	else //else if (acb == 0b11010000)
		param1 = consume_param(vm->arena, &cursor->pc, 2);
	param2 = consume_param(vm->arena, &cursor->pc, 1);
	cursor->reg[param2] = (cursor->pc + (param1 % IDX_MOD)) % MEM_SIZE;
}

void	cw_st(t_vm *vm, t_process *cursor)
{
	unsigned char	acb;
	int				param1;

	cursor->pc++;
	acb = vm->arena[cursor->pc++];
	int test = consume_param(vm->arena, &cursor->pc, 1);
	printf("reg index %d\n", test);
	param1 = cursor->reg[test];
	test = consume_param(vm->arena, &cursor->pc, 2);
	printf("reg index %d\n", test);
	if (acb == 0b01110000)
		itouc(&vm->arena[test % MEM_SIZE], param1);
	else if (acb == 0b01010000)
		cursor->reg[consume_param(vm->arena, &cursor->pc, 1)] = param1;
}

void	cw_add(t_vm *vm, t_process *cursor)
{
	int	param1;
	int	param2;

	cursor->pc++;
	param1 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	param2 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	cursor->reg[consume_param(vm->arena, &cursor->pc, 1)] = param1 + param2;
}
