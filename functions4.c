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

void	cw_lld(t_vm *vm, t_process *cursor, int start)
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
		if (acb & 0b01000000 > 0)
			p[0] = cursor->reg[p[0]];
		index = (start + p[0]) % MEM_SIZE;
		cursor->reg[p[1]] = vm_read(vm, &index, 4);
	}
}

void	cw_lldi(t_vm *vm, t_process *cursor, int start)
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
		if (acb & 0b01000000 > 0)
			p[0] = cursor->reg[p[0]];
		if (acb & 0b00010000 > 0)
			p[1] = cursor->reg[p[1]];
		index = (start + p[0] + p[1]) % MEM_SIZE;
		cursor->reg[p[2]] = vm_read(vm, &index, 4);
	}
}

void	cw_lfork(t_vm *vm, t_process *cursor, int start)
{
	t_process	*newcursor;
	int			param1;

	cursor->pc++;
	param1 = vm_read(vm, &cursor->pc, 4);
	newcursor = clone_cursor(cursor, (start + param1) % MEM_SIZE);
	newcursor->carry = 0;
	add_cursor(vm, newcursor);
}

void	cw_aff(t_vm *vm, t_process *cursor, int start)
{
	int param1;

	cursor->pc++;
	param1 = vm_read(vm, &cursor->pc, 1);
	ft_putchar(cursor->reg[param1] % 256);
}