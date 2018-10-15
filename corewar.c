/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 11:42:54 by agabrie           #+#    #+#             */
/*   Updated: 2018/09/21 09:17:48 by mgerber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "corewar.h"

t_vm	*g_vm;

static void	(*cw_funcs[16])(t_vm *vm, t_process *cursor) = {
	cw_live, cw_ld,   cw_st,   cw_add, 
	cw_sub,  cw_and,  cw_or,   cw_xor,
	cw_zjmp, cw_ldi,  cw_sti,   cw_fork,
	cw_lld,  cw_lldi, cw_lfork, cw_aff
};

int		main(int ac, char **av)
{
	t_vm		vm;

	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(64*4, 64*4);
	glutCreateWindow("corewar");
	glDisable(GL_DEPTH_TEST);
	glutDisplayFunc(run_vm);
	glutIdleFunc(run_vm);

	init(&vm);
	if (ac > 1)
	{
		ft_putstr("count_champs\n");
		count_champs(&vm, ac, av);
		ft_nbrendl(vm.num_champs);
		ft_putstr("load_vm\n");
		load_vm(&vm);
	}
	//printf("%p\n", vm.first);
	g_vm = &vm;
	glPixelZoom(4.0, 4.0);
	ft_putarena(vm.arena, 64 * 64);
	glutMainLoop();
	//run_vm(&vm);
}

void	execute_process(t_vm *vm, t_process *cursor)
{
	//printf("exec %d waitcycles %d\n", vm->arena[cursor->pc], cursor->waitcycles);
	int op;

	op = 0;
	while (op < 3)
	{
		cursor->is_reg[op] = 0;
		cursor->params[op] = 0;
		op++;
	}
	op = vm->arena[cursor->pc];
	if (cursor->waitcycles == 0) printf("%d %d %d %d %d %d %d %d\n",
		vm->arena[MEM(cursor->pc+0)],
		vm->arena[MEM(cursor->pc+1)],
		vm->arena[MEM(cursor->pc+2)],
		vm->arena[MEM(cursor->pc+3)],
		vm->arena[MEM(cursor->pc+4)],
		vm->arena[MEM(cursor->pc+5)],
		vm->arena[MEM(cursor->pc+6)],
		vm->arena[MEM(cursor->pc+7)]
	);
	if (cursor->waitcycles)
	{
		cursor->waitcycles--;
	}
	else if ((op > 0 && op < 17)
		&& check_args(vm, &vm->op_tab[op], cursor))
	{
		printf("\t\t\t\texec [%s] at %d\n", vm->op_tab[op].name, cursor->start);
		cursor->waitcycles = vm->op_tab[op].cycles;
		printf("going into cw_funcs\n");
		cw_funcs[op - 1](vm, cursor);

	}
	else if (!(op > 0 && op < 17))
	{
		printf("%d not an op\n", op);
		cursor->pc++;
	}
	else
		cursor->pc++;
}

void	run_vm(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	t_process	*cursor;
	t_vm		*vm;

	vm = g_vm;

	//printf("gg %p\n", cursor);
	cursor = vm->first;
	int gg = 0;
	while (cursor)
	{
		//printf("cursor: %d\n", cursor->pc);
		//printf("%d\n", cursor->pc);
		if (!cursor->dead_flag)
		{
			execute_process(vm, cursor);
		}
		if (cursor->pc < 0)
		{
			printf("cursor tooo small abort mission!!!\n");
			cursor->pc = MEM_SIZE - (cursor->pc * -1);
		}
		cursor->pc = cursor->pc % MEM_SIZE;
		cursor = cursor->next;
		gg++;
	}
	//printf("\t\t\t\t\t\t\t\t\t\tncursors %d\n", gg);
	vm->total_cycles++;
	vm->cycle--;
	if (!vm->cycle)
	{
		//kill_cursors(vm);
		if (vm->lives >= NBR_LIVE)
		{
			if (!(vm->cycle_to_die < CYCLE_DELTA))
				vm->cycle_to_die -= CYCLE_DELTA;
		}
		vm->cycle = vm->cycle_to_die;
	}


	int i = 0;
	//while (i < 64 * 64)
	//{
	//	if (vm->pixels[i] != 0xf0f0f0f0)
	//		vm->pixels[64*64 - 1 - i] = 0;
	//	i++;
	//}
	//i = 0;
	while (i < 64 * 64)
	{
	//	if (vm->arena[i] != 0 &&vm->pixels[i] != 0xf0f0f0f0)
			vm->pixels[64*64 - 1 - i] = vm->arena[i] * 50000;
		i++;
	}
	cursor = vm->first;
	while (cursor)
	{
		if (vm->total_cycles % 2 == 0)
			vm->pixels[64*64 - 1 - (abs(cursor->pc)%MEM_SIZE)] = 0xf0000000;
		else 
			vm->pixels[64*64 - 1 - (abs(cursor->pc)%MEM_SIZE)] = 0xf0555500;
		cursor = cursor->next;
	}
	glDrawPixels(64, 64, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, vm->pixels);
	glutSwapBuffers();
	glFlush();
	//}
	//exit_sequence(vm);
}
