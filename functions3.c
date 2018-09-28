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

void	cw_zjmp(t_vm *vm, t_process *cursor, int start)
{
	int		p;

	cursor->pc++;
	p = vm_read(vm, &cursor->pc, 2);
	cursor->pc = (start + p) % MEM_SIZE;
}

void	cw_ldi(t_vm *vm, t_process *cursor, int start)
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
		index = ((start + p[0] + p[1]) % IDX_MOD) % MEM_SIZE;
		cursor->reg[p[2]] = vm_read(vm, &index, 4);
	}
}

void	cw_sti(t_vm *vm, t_process *cursor, int start)
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
		p[0] = cursor->reg[p[0]];
		if (acb & 0b00010000 > 0)
			p[1] = cursor->reg[p[1]];
		if (acb & 0b00000100 > 0)
			p[2] = cursor->reg[p[2]];
		index = ((start + p[1] + p[2]) % IDX_MOD) % MEM_SIZE;
		vm_write(vm, index, p[0], 4);
	}
}

void	cw_fork(t_vm *vm, t_process *cursor, int start)
{
	t_process	*newcursor;
	int			param1;

	cursor->pc++;
	param1 = vm_read(vm, &cursor->pc, 2);
	newcursor = clone_cursor(cursor, (start + (param1 % IDX_MOD)) % MEM_SIZE);
	newcursor->carry = 0;
	add_cursor(vm, newcursor);
}
