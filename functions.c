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

void	cw_live(t_vm *vm, t_process *cursor, int start)
{
	int i;

	i = 0;
	printf("num_champs%d\n", vm->num_champs);
	while (i < vm->num_champs)
	{
		printf("%d, %d\n", cursor->pc, i);
		if (vm->champs[i].number == uctoi(&vm->arena[cursor->pc + 1], 4))
		{
			vm->champs[i].lives++;
			vm->champs[i].last_live = vm->total_cycles;
		}
		i++;
	}
	cursor->live_flag = 1;
	cursor->pc += 5;
}

void	cw_ld(t_vm *vm, t_process *cursor, int start)
{
	unsigned char	acb;
	int				param1;
	int				param2;

	// "invalid write of size 4" apparently...
	cursor->pc++;
	acb = vm->arena[cursor->pc++];
	if (acb == 0b10010000)
	{
		cursor->pc %= MEM_SIZE;
		param1 = consume_param(vm->arena, &cursor->pc, 4);
		
	}
	else //else if (acb == 0b11010000)
	{
		cursor->pc %= MEM_SIZE;
		param1 = consume_param(vm->arena, &cursor->pc, 2);
	}
	cursor->pc %= MEM_SIZE;
	param2 = consume_param(vm->arena, &cursor->pc, 1);
	printf("before write reg %d\n", param2);
	if (param2 < 16)
	{
		cursor->reg[param2] = (start + (param1 % IDX_MOD)) % MEM_SIZE;
	}
	printf("after write\n");
}

void	cw_st(t_vm *vm, t_process *cursor, int start)
{
	unsigned char	acb;
	int				param1;

	// Access not within mapped region at address 0x12507004
	cursor->pc++;
	acb = vm->arena[cursor->pc++];
	int test = consume_param(vm->arena, &cursor->pc, 1);
	if (test > 15)
	{
		cursor->pc += 3;
		return ;
	}
	printf("reg index %d\n", test);
	param1 = cursor->reg[test];
	test = consume_param(vm->arena, &cursor->pc, 2);
	printf("reg index %d\n", test);
	if (acb == 0b01110000)
		itouc(&vm->arena[(start + (test % IDX_MOD)) % MEM_SIZE], param1);
	else if (acb == 0b01010000)
		cursor->reg[consume_param(vm->arena, &cursor->pc, 1)] = param1;
}

void	cw_add(t_vm *vm, t_process *cursor, int start)
{
	int	param1;
	int	param2;

	cursor->pc++;
	printf("b1\n"); // "invalid read of size 4" on both of these apparently...
	param1 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	printf("b2\n");
	param2 = cursor->reg[consume_param(vm->arena, &cursor->pc, 1)];
	printf("b3\n");
	cursor->reg[consume_param(vm->arena, &cursor->pc, 1)] = param1 + param2;
	printf("b4\n");
}
