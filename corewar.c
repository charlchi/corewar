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

int		main(int ac, char **av)
{
	t_vm		vm;

	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(64*10, 64*10);
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
	printf("%p\n", vm.first);
	g_vm = &vm;
	glPixelZoom(10.0, 10.0);
	glutMainLoop();
	//run_vm(&vm);
}

void	run_vm(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int			pixels[64 * 64];



	t_process	*cursor;
	t_vm		*vm;

	vm = g_vm;

	cursor = vm->first;
	int gg = 0;
	while (cursor)
	{
		//printf("exec cursor %d\n", gg);
		if (!cursor->dead_flag)
			execute_process(vm, cursor);
		//if (cursor->pc < 0) cursor->pc = ((cursor->pc * - 1) % MEM_SIZE);
		cursor->pc = cursor->pc % MEM_SIZE;
		//printf("%d pc %d \n", gg, cursor->pc);
		cursor = cursor->next;
		gg++;
	}
	//printf("number of cursors----------------->%d\n", gg);
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
	while (i < 64 * 64)
	{
		pixels[64*64 - 1 - i] = vm->arena[i] * 50000;
		i++;
	}
	cursor = vm->first;
	while (cursor)
	{
		if (vm->total_cycles % 8 < 4)
			pixels[64*64 - 1 - (cursor->pc%MEM_SIZE)] = 0xf0000000;
		else 
			pixels[64*64 - 1 - (cursor->pc%MEM_SIZE)] = 0xf0555500;
		cursor = cursor->next;
	}
	glDrawPixels(64, 64, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, pixels);
	glutSwapBuffers();
	glFlush();
	//}
	//exit_sequence(vm);
}
