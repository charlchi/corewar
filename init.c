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

#define READ_ERR(fd, p, siz, str) if (read(fd, p, siz) < 1) \
	{ft_putendl(str); exit(0);}

int		main(int ac, char **av)
{
	t_vm		vm;

	if (ac < 2)
	{
		//todo print usage
		exit(0);
	}
	init_vm(&vm);
	load_champs(&vm, ac, av);
	load_vm(&vm);
	run_vm(&vm);
}

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
	ft_bzero(vm->arena, MEM_SIZE);
	ft_bzero(vm->colors, MEM_SIZE);
	set_op_tab(vm);
}

int		ft_contains(char *whole, char *part)
{
	int		i;
	int		j;
	int		valid;

	i = -1;
	j = 0;
	valid = 0;
	while (++i <= (int)ft_strlen(whole))
	{
		if (valid == (int)ft_strlen(part))
			return (1);
		if (whole[i] == part[j++])
			valid++;
		else
		{
			valid = 0;
			j = 0;
		}
	}
	return (0);
}

void	count_champ(t_vm *vm, char *file)
{
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 1)
	{
		ft_putstr("Error opening champion file : ");
		ft_putstr(file);
		ft_putstr("\n");
		exit(1);
	}
	vm->champs[vm->num_champs].number = vm->num_champs;
	vm->champs[vm->num_champs].path = ft_strdup(file);
	vm->champs[vm->num_champs].last_live = 0;
	vm->champs[vm->num_champs].lives = 0;
	vm->num_champs++;
	close(fd);
}

void	load_champs(t_vm *vm, int ac, char **av)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] != '-')
			count_champ(vm, av[i]);
		if (ft_strcmp(av[i], "-n") == 0)
			if (av[i + 1] == NULL || ft_atoi(av[i + 1]) == 0)
				ft_putstr("Expected valid number after -n argument\n");
		if (ft_strncmp(av[i], "-v", 2) == 0)
			vm->v = atoi(&av[i][2]);
		if (ft_strncmp(av[i], "-d", 2) == 0)
			vm->dump = atoi(&av[i][2]);
		i++;
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
	{
		ft_putendl("Not valid corewar champion!");
		exit(0);
	}
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
		vm->champs[p].start = vm->champs[p].number * (MEM_SIZE / vm->num_champs);
		cur = create_cursor(vm->champs[p].start);
		cur->waitcycles = 0;
		cur->reg[0] = 0xffffffff - p;
		vm->champs[p].number = (0x00ffffff) + ((0xff - p) << 24);
		i = 1;
		while (i < 16)
			cur->reg[i++] = 0;
		add_cursor(vm, cur);
		place_player(vm, p);
		ft_putstr("* Player ");
		ft_putnbr(p + 1);
		ft_putstr(", ");
		ft_putstr((char *)vm->champs[p].prog_name);
		ft_putstr("\n");
		p++;
	}
}
