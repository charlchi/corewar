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

#define READ_ERR(f, p, s, t) if (read(f, p, s) < 1) {ft_putendl(t); exit(0);}
#define ERRP(x) {ft_putstr(x); ft_putstr("\n"); exit(0);}

void	init_vm(t_vm *vm)
{
	vm->num_champs = 0;
	vm->first = NULL;
	vm->total_cycles = 0;
	vm->cycle = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->lives = 0;
	vm->checks = 0;
	vm->v = 0;
	vm->dump = -1;
	vm->cycle = vm->cycle_to_die;
	vm->nolive = 0;
	vm->n = -1;
	vm->last_livep = -1;
	ft_bzero(vm->arena, MEM_SIZE);
	ft_bzero(vm->colors, MEM_SIZE);
	set_op_tab(vm);
}

void	count_champ(t_vm *vm, char *file)
{
	int		fd;
	int		p;

	if ((fd = open(file, O_RDONLY)) < 1)
	{
		ft_putstr("Error opening champion file : ");
		ERRP(file);
	}
	if (vm->n != -1)
		vm->champs[vm->num_champs].number = vm->n;
	else
		vm->champs[vm->num_champs].number = vm->num_champs;
	p = -1;
	while (++p < vm->num_champs)
	{
		if (vm->champs[vm->num_champs].number == vm->champs[p].number)
			ERRP("Duplicate champion numbers!");
	}
	vm->champs[vm->num_champs].path = file;
	vm->champs[vm->num_champs].last_live = 0;
	vm->champs[vm->num_champs].lives = 0;
	vm->num_champs++;
	close(fd);
}

void	load_champs(t_vm *vm, int ac, char **av)
{
	int		i;

	i = 0;
	while (++i < ac)
	{
		if (av[i][0] != '-')
			count_champ(vm, av[i]);
		vm->n = -1;
		if (ft_strcmp(av[i], "-n") == 0)
		{
			i++;
			if (av[i] == NULL || (vm->n = ft_atoi(av[i])) == 0)
				ERRP("Expected valid number after -n argument");
		}
		if (ft_strncmp(av[i], "-v", 2) == 0)
			if ((vm->v = atoi(&av[i][2])) <= 0 || vm->v > 2)
				ERRP("Invalid number after -v");
		if (ft_strncmp(av[i], "-dump", 5) == 0)
		{
			i++;
			if (av[i] == NULL || (vm->dump = atoi(av[i])) == 0)
				ERRP("Expected valid number after -dump argument");
		}
	}
}

void	place_player(t_vm *vm, int pnum)
{
	int			i;
	int			ret;
	t_champ		*ch;

	ch = &vm->champs[pnum];
	ch->fd = open(ch->path, O_RDONLY);
	if (ch->fd < 1)
		exit(1);
	READ_ERR(ch->fd, ch->magic, 4, "Exec Magic Incomplete");
	if (*((unsigned int *)&ch->magic[0]) != 0xf383ea00)
		ERRP("Not valid corewar champion!");
	READ_ERR(ch->fd, ch->prog_name, PROG_NAME_LENGTH - 4, "Program name err");
	READ_ERR(ch->fd, ch->size, 12, "Invalid program size");
	READ_ERR(ch->fd, ch->prog_comment, COMMENT_LENGTH + 4, "Invalid Comment");
	ch->p_size = (ch->size[11] + ((int)ch->size[10] << 8) + 1);
	ch->core = malloc(sizeof(unsigned char) * ch->p_size);
	i = 0;
	while ((ret = read(ch->fd, ch->core + i, 1)) > 0)
	{
		vm->colors[ch->start + i] = pnum + 1;
		i++;
	}
	ch->p_size = i;
	ft_memcpy(&vm->arena[ch->start], ch->core, ch->p_size);
	free(ch->core);
}

void	load_vm(t_vm *vm)
{
	int			i;
	int			p;
	t_process	*cur;

	p = 0;
	ft_putstr("Introducing contestants...\n");
	while (p < vm->num_champs)
	{
		vm->champs[p].start = p * (MEM_SIZE / vm->num_champs);
		cur = create_cursor(vm->champs[p].start);
		cur->waitcycles = 0;
		i = 1;
		while (i < 16)
			cur->reg[i++] = 0;
		add_cursor(vm, cur);
		place_player(vm, p);
		cur->reg[0] = vm->champs[p].number;
		ft_putstr("* Player ");
		ft_putnbr(vm->champs[p].number);
		ft_putstr(", ");
		ft_putstr((char *)vm->champs[p].prog_name);
		ft_putstr("\n");
		p++;
	}
}
