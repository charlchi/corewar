/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 09:11:05 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/21 09:16:35 by mgerber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				check_acb(t_vm *vm, char opcode, char acb)
{
	int		i;
	int		code;

	i = 0;
	
	printf("inside check_acb %s\n", vm->op_tab[opcode - 1].name);

	if (vm->op_tab[opcode - 1].nargs > 1)
	{
		printf("%d\n", (vm->op_tab[opcode - 1].argtype[0] & 
			((acb >> 6) & 0b00000011)));
		if ((vm->op_tab[opcode - 1].argtype[0] & 
			((acb >> 6) & 0b00000011)) == 0)
			return (0);
	}
	if (vm->op_tab[opcode - 1].nargs > 2)
	{
		if ((vm->op_tab[opcode - 1].argtype[1] & 
			((acb >> 4) & 0b00000011)) == 0)
			return (0);
	}
	if (vm->op_tab[opcode - 1].nargs > 3)
	{
		if ((vm->op_tab[opcode - 1].argtype[2] & 
			((acb >> 2) & 0b00000011)) == 0)
			return (0);
	}
	printf("check_acb succesfull\n");
	return (1);
}

int				vm_read_params(t_vm *vm, int *pc, unsigned int *p, char acb)
{
	int		size;

	size = vm->op_tab[vm->arena[*(pc - 1)] - 1].label_size ? 2 : 4;
	if (((acb & 0b11000000) >> 6) == REG_CODE){
		if ((p[0] = vm_read(vm, pc, 1)) > 15)
			return (0);
	}
	else if (((acb & 0b11000000) >> 6) == IND_CODE)
		p[0] = vm_read(vm, pc, 2);
	else if (((acb & 0b11000000) >> 6) == DIR_CODE)
		p[0] = vm_read(vm, pc, size);
	if (((acb & 0b00110000) >> 4) == REG_CODE)
	{
		if ((p[1] = vm_read(vm, pc, 1)) > 15)
			return (0);
	}
	else if (((acb & 0b00110000) >> 4) == IND_CODE)
		p[1] = vm_read(vm, pc, 2);
	else if (((acb & 0b00110000) >> 4) == DIR_CODE)
		p[1] = vm_read(vm, pc, size);
	if (((acb & 0b00001100) >> 2) == REG_CODE)
	{
		if ((p[2] = vm_read(vm, pc, 1)) > 15)
			return (0);
	}
	else if (((acb & 0b00001100) >> 2) == IND_CODE)
		p[2] = vm_read(vm, pc, 2);
	else if (((acb & 0b00001100) >> 2) == DIR_CODE)
		p[2] = vm_read(vm, pc, size);
	//printf("%d %d %d\n", p[0], p[1], p[2]);
	return (1);
}

unsigned int	vm_read(t_vm *vm, int *pos, int n)
{
	int				i;
	unsigned int	ret;

	ret = 0;
	i = 0;
	while (i < n)
	{
		printf("read %d %x\n", (*pos), vm->arena[(*pos) % MEM_SIZE]);
		ret = ret << 8;
		ret += vm->arena[(*pos)++ % MEM_SIZE];
		i++;
	}
	*pos = *pos % MEM_SIZE;
	return (ret);
}

void			vm_write(t_vm *vm, int pos, int val, int n)
{
	if (n == 1)
	{
		vm->arena[pos % MEM_SIZE] = (char)(val & 0x000000ff);
	}
	else if (n == 2)
	{
		vm->arena[(pos + 0) % MEM_SIZE] = (char)(val & 0x0000ff00);
		vm->arena[(pos + 1) % MEM_SIZE] = (char)(val & 0x000000ff);
	}
	else if (n == 4)
	{
		vm->arena[(pos + 0) % MEM_SIZE] = (char)(val & 0xff000000);
		vm->arena[(pos + 1) % MEM_SIZE] = (char)(val & 0x00ff0000);
		vm->arena[(pos + 2) % MEM_SIZE] = (char)(val & 0x0000ff00);
		vm->arena[(pos + 3) % MEM_SIZE] = (char)(val & 0x000000ff);
	}
}

unsigned int	uctoi(unsigned char *pos, int bytes)
{
	int				i;
	unsigned int	ret;

	ret = pos[0];
	i = 1;
	while (i < bytes)
	{
		ret = ret << 8;
		ret += pos[i];
		i++;
	}
	return (ret);
}

void			itouc(unsigned char *pos, unsigned int num)
{
	pos[0] = (num & 0xff000000) >> 24;
	pos[1] = (num & 0x00ff0000) >> 16;
	pos[2] = (num & 0x0000ff00) >> 8;
	pos[3] = (num & 0x000000ff);
}

int				is_action(t_vm *vm, unsigned char c)
{
	int k;

	if (c >= 1 && c <= 16)
		return (c);
	return (0);
}

unsigned int		consume_param(unsigned char *pos, int *pc, int bytes)
{
	unsigned int		ret;

	ret = uctoi(pos + *pc, bytes);
	*pc += bytes;
	return (ret);
}
