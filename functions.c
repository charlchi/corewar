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
	int		num;
	int i;

	i = 0;
	cursor->pc++;
	num = vm_read(vm, &cursor->pc, 4);
	while (i < vm->num_champs)
	{
		if (vm->champs[i].number == num)
		{
			vm->champs[i].lives++;
			vm->champs[i].last_live = vm->total_cycles;
		}
		i++;
	}
	cursor->live_flag = 1;
}

void	cw_ld(t_vm *vm, t_process *cursor, int start)
{
	unsigned char	acb;
	int				index;
	int				p[3];

	cursor->pc++;
	acb = (char)vm_read(vm, &cursor->pc, 1);
	printf("test %x\n", acb);
	if (!check_acb(vm, vm->arena[start], acb))
		return ;
	printf("test\n");
	ft_bzero((void *)p, sizeof(p));
	if (vm_read_params(vm, &cursor->pc, p, acb))
	{
		printf("test\n");
		if ((acb & 0b01000000) > 0)
		{
			p[0] = cursor->reg[p[0]];
		}
		index = (start + (p[0] % IDX_MOD)) % MEM_SIZE;
		cursor->reg[p[1]] = vm_read(vm, &index, 4);
	}
}




void	cw_st(t_vm *vm, t_process *cursor, int start)
{
	unsigned char	acb;
	int				index;
	int				p[3];

	cursor->pc++;
	acb = (char)vm_read(vm, &cursor->pc, 1);
	if (!check_acb(vm, vm->arena[start], acb))
		return ;
	ft_bzero((void *)p, sizeof(p));
	if (vm_read_params(vm, &cursor->pc, &p[0], acb))
	{
		if (acb == 0b01110000)
		{
			index = (((start + (p[1] % IDX_MOD))) % MEM_SIZE);
			vm_write(vm, index, cursor->reg[p[0]], 4);
		}
		else if (acb == 0b01010000)
			cursor->reg[p[1]] = cursor->reg[p[0]];
	}
}

void	cw_add(t_vm *vm, t_process *cursor, int start)
{
	unsigned char	acb;
	int				p[3];
	
	cursor->pc++;
	acb = (char)vm_read(vm, &cursor->pc, 1);
	if (!check_acb(vm, vm->arena[start], acb))
		return ;
	ft_bzero((void *)p, sizeof(p));
	if (vm_read_params(vm, &cursor->pc, &p[0], acb))
		cursor->reg[p[2]] = cursor->reg[p[0]] + cursor->reg[p[1]];
}
