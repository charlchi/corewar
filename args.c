/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:44:53 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/24 16:48:06 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_args_nocode(t_vm *vm, t_op *op, t_process *cursor)
{
	int		val;
	int		jump;

	val = read_arg(vm, cursor->pc + 1, op->argtype[0], op->label_size);
	if ((op->argtype[0] & T_REG) && (val < 0 || val > 15))
		return (0);
	else if (op->argtype[0] & T_REG)
		cursor->is_reg[0] = 1;
	cursor->params[0] = val;
	jump = code_size(op->argtype[0], op->label_size);
	cursor->pc += jump + 1;
	return (1);
}

int		check_args(t_vm *vm, t_op *op, t_process *cursor)
{
	int			i;
	int			read;
	int			code;

	cursor->start = cursor->pc;
	if (op->acb == 0)
		return (check_args_nocode(vm, op, cursor));
	read = cursor->pc + 2;
	i = -1;
	while (++i < op->nargs)
	{
		code = (((vm->arena[MEM(cursor->pc + 1)]) >> (6 - (i * 2))) & 3);
		code += (code == 3 ? 1 : 0);
		if ((op->argtype[i] & code) == 0)
			return (0);
		if ((code == T_REG && (vm->arena[MEM(read)] < 1
			|| vm->arena[MEM(read)] > 16)))
			return (0);
		else if (code == T_REG)
			cursor->is_reg[i] = 1;
		cursor->params[i] = read_arg(vm, read, code, op->label_size);
		read += code_size(code, op->label_size);
	}
	cursor->pc = MEM(read);
	return (1);
}

int		code_size(int code, int label_size)
{
	if (code == T_REG)
		return (1);
	else if (code == T_DIR && label_size == 0)
		return (4);
	else if (code == T_IND || (code == T_DIR && label_size))
		return (2);
	return (0);
}

int		read_arg(t_vm *vm, int pos, int code, int label_size)
{
	int			ret;

	if (code == T_REG)
	{
		ret = vm->arena[MEM(pos)] - 1;
	}
	else if (code == T_DIR && label_size == 0)
	{
		ret = vm->arena[MEM(pos + 3)] << 0;
		ret += (vm->arena[MEM(pos + 2)]) << 8;
		ret += (vm->arena[MEM(pos + 1)]) << 16;
		ret += (vm->arena[MEM(pos + 0)]) << 24;
	}
	else
	{
		ret = (vm->arena[MEM(pos + 1)]);
		ret += (vm->arena[MEM(pos + 0)]) << 8;
		ret = (short)ret;
	}
	return (ret);
}
