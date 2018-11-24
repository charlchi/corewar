/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:15:16 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/24 17:15:17 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "op.h"

static t_op		g_op_tab[17] = {
	{"", 0, {0, 0, 0}, 0, 0, "", 0, 0},
	{"live", 1, {T_DIR, 0, 0}, 1, 10,
		"alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG, 0}, 2, 5,
		"load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG, 0}, 3, 5,
		"store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10,
		"addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10,
		"soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR, 0, 0}, 9, 20,
		"jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR, 0, 0}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG, 0}, 13, 10,
		"long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"", 1, 1},
	{"lfork", 1, {T_DIR, 0, 0}, 15, 1000, "t", 0, 1},
	{"aff", 1, {T_REG, 0, 0}, 16, 2, "t", 1, 0}
};

void		set_op_tab(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < 18)
	{
		vm->op_tab[i] = g_op_tab[i];
		i++;
	}
}
