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
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#include <GLUT/glut.h>

t_vm	*g_vm;

int		main(int ac, char **av)
{
	t_vm		vm;

	int wd;
	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(64*4, 64*4);
	wd = glutCreateWindow("corewar");
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
		ft_putstr("putarena\n");
		ft_putarena(vm.arena, MEM_SIZE);
	}
	printf("%p\n", vm.first);
	g_vm = &vm;
	glPixelZoom(4.0, 4.0);
	glutMainLoop();
	//run_vm(&vm);
}

void	run_vm(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int			pixels[64 * 64];



	t_process	*cursor;
	t_vm		*vm;

	vm = g_vm; // remove this
	ft_putstr("still running ");
	ft_putnbr(vm->total_cycles);
	ft_putstr("\n");

	cursor = vm->first;
	while (cursor)
	{
		if (!cursor->dead_flag)
			execute_process(vm, cursor);
		cursor = cursor->next;
	}
	vm->total_cycles++;
	vm->cycle--;
	if (!vm->cycle)
	{
		kill_cursors(vm);
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
		pixels[i] = vm->arena[i] * 5000;
		i++;
	}
	glDrawPixels(64, 64, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, pixels);
	glutSwapBuffers();
	glFlush();
	//}
	//exit_sequence(vm);
}
