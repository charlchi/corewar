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
	vm->v = 0;
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

void	load_champs(t_vm *vm, int ac, char **av)
{
	int		i;
	int		fd;

	i = 1;
	fd = 0;
	while (i < ac)
	{
		if (av[i][0] != '-')
		{
			if ((fd = open(av[i], O_RDONLY)) < 1)
			{
				ft_putstr("Error opening champion file : ");
				ft_putstr(av[i]);
				ft_putstr("\n");
				exit(1);
			}
			vm->champs[vm->num_champs].number = vm->num_champs;
			vm->champs[vm->num_champs].path = ft_strdup(av[i]);
			vm->num_champs++;
			close(fd);
		}
		if (ft_strequ(av[i], "-v"))
			vm->v = 1;
		if (ft_strequ(av[i], "-d"))
			vm->v = -1;
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
	if (ch->fd > 0)
		ft_putstr("champion exists : \n");
	else
		exit(1);
	printf("%d %s\n", pnum, ch->path);
	READ_ERR(ch->fd, ch->magic, 4, "Exec Magic Incomplete");
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
	ft_putstr("Loaded player succesfully\n");
}

void	load_vm(t_vm *vm)
{
	int			i;
	int			p;
	t_process	*cur;

	p = 0;
	while (p < vm->num_champs)
	{
		printf("creating one player\n");
		vm->champs[p].start = vm->champs[p].number * (MEM_SIZE / vm->num_champs);
		cur = create_cursor(vm->champs[p].start);
		cur->waitcycles = 0;
		cur->reg[0] = 0xffffffff - p;
		i = 1;
		while (i < 16)
			cur->reg[i++] = 0;
		add_cursor(vm, cur);
		place_player(vm, p);
		p++;
	}
	ft_putstr("Done load_vm\n");
}
