/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 17:01:09 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/24 17:01:20 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			main(int ac, char **av)
{
	t_vm		vm;

	if (ac < 2)
		print_usage();
	init_vm(&vm);
	load_champs(&vm, ac, av);
	load_vm(&vm);
	run_vm(&vm);
}

void		dump_vm(t_vm *vm)
{
	int			i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i != 0 && i % 64 == 0)
			printf("\n");
		if (i % 64 == 0)
			printf("0x%04x : ", i);
		printf("%02x", vm->arena[i]);
		i++;
	}
	printf("\n");
}

void		print_usage(void)
{
	ft_putstr("Usage: ./corewar -n 5 champ1.cor -n 6");
	ft_putstr(" champ2.cor -dump [num cycles] -v[1 or 2]\n");
	exit(0);
}
