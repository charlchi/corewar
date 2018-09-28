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

void	cw_sub(t_vm *vm, t_process *cursor, int start)
{
	unsigned char	acb;
	int				p[3];
	
	cursor->pc++;
	acb = (char)vm_read(vm, &cursor->pc, 1);
	if (!check_acb(vm, vm->arena[start], acb))
		return ;
	ft_bzero((void *)p, sizeof(p));
	if (vm_read_params(vm, &cursor->pc, &p[0], acb))
		cursor->reg[p[2]] = cursor->reg[p[0]] - cursor->reg[p[1]];
}

void	cw_and(t_vm *vm, t_process *cursor, int start)
{
	unsigned char	acb;
	int				p[3];
	
	cursor->pc++;
	acb = (char)vm_read(vm, &cursor->pc, 1);
	if (!check_acb(vm, vm->arena[start], acb))
		return ;
	ft_bzero((void *)p, sizeof(p));
	if (vm_read_params(vm, &cursor->pc, &p[0], acb))
	{
		if ((acb & 0b01000000) > 0)
			p[0] = cursor->reg[p[0]];
		if ((acb & 0b00010000) > 0)
			p[1] = cursor->reg[p[1]];
		cursor->reg[p[2]] = p[0] & p[1];;
	}
}

void	cw_or(t_vm *vm, t_process *cursor, int start)
{
	unsigned char	acb;
	unsigned int	p[3];
	
	cursor->pc++;
	acb = (char)vm_read(vm, &cursor->pc, 1);
	if (!check_acb(vm, vm->arena[start], acb))
		return ;
	ft_bzero((void *)p, sizeof(p));
	if (vm_read_params(vm, &cursor->pc, &p[0], acb))
	{
		if ((acb & 0b01000000) > 0)
			p[0] = cursor->reg[p[0]];
		if ((acb & 0b00010000) > 0)
			p[1] = cursor->reg[p[1]];
		cursor->reg[p[2]] = p[0] | p[1];;
	}
}

void	cw_xor(t_vm *vm, t_process *cursor, int start)
{
	unsigned char	acb;
	int				p[3];
	
	cursor->pc++;
	acb = (char)vm_read(vm, &cursor->pc, 1);
	if (!check_acb(vm, vm->arena[start], acb))
		return ;
	ft_bzero((void *)p, sizeof(p));
	if (vm_read_params(vm, &cursor->pc, &p[0], acb))
	{
		if ((acb & 0b01000000) > 0)
			p[0] = cursor->reg[p[0]];
		if ((acb & 0b00010000) > 0)
			p[1] = cursor->reg[p[1]];
		cursor->reg[p[2]] = p[0] ^ p[1];;
	}
}
