/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agabrie <agabrie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 11:30:58 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/21 09:56:55 by agabrie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define READ_ERR(fd, p, siz, str) if (read(fd, p, siz) < 1) ERROR(str)
#define ERROR(str) (col_endl_fd(FRED, str, 1),exit(0))

/********** AGABRIE LIBFT STUFF *******************/

#define RSET "\033[00m"
#define FBLK "\033[30m"
#define FRED "\033[31m"
#define FGRN "\033[32m"
#define FYEL "\033[33m"
#define FBLU "\033[34m"
#define FMAG "\033[35m"
#define FCYN "\033[36m"
#define FWHT "\033[37m"

void	col_endl_fd(char *colour, char *str, int fd)
{
	col_str_fd(colour, str, fd);
	col_str_fd(colour, "\n", fd);
}

void	col_char_fd(char *colour, char c, int fd)
{
	col_str_fd(colour, &c, fd);
}

void	col_str_fd(char *colour, char *str, int fd)
{
	ft_putstr_fd(colour, fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(RSET, fd);
}

void			ft_nbrendl_fd(int nbr, int fd)
{
	ft_putnbr_fd(nbr, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_nbrendl(int nbr)
{
	ft_nbrendl_fd(nbr, 2);
}

void	ft_putarr_fd(char **arr, int fd)
{
	int i;

	i = 0;
	while (arr[i] != '\0')
		ft_putendl_fd(arr[i++], fd);
}

int		ft_contains(char *whole, char *part)
{
	int i;
	int j;
	int valid;

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

/********************END***********************/

void count_champs(t_vm *vm, int ac, char **av)
{
	int i = 1;
	int fd = 0;
	while (i < ac)
	{
		if (ft_contains(av[i], ".cor"))
		{
			fd = open(av[i], O_RDONLY);
			if (fd < 1)
			{
				col_str_fd(FRED, "Invalid File\t:\t", 1);
				ft_putendl_fd(av[i], 1);
				exit(1);
			}
			else
			{
				vm->champs[vm->num_champs].ldnbr = vm->num_champs;
				vm->champs[vm->num_champs].number = vm->num_champs;
				vm->champs[vm->num_champs].name = ft_strdup(av[i]);
				ft_putendl_fd(vm->champs[vm->num_champs].name, 1);
				vm->num_champs++;
				col_str_fd(FGRN, "Valid File\t:\t", 1);
				ft_putendl_fd(av[i], 1);
			}
			close(fd);
		}
		i++;
	}
	printf("number of champs %d\n", vm->num_champs);
}

void	init(t_vm *vm)
{
	vm->num_champs = 0;
	vm->first = NULL;
	vm->total_cycles = 0;
	vm->cycle = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->lives = 0;
	ft_bzero(vm->arena, MEM_SIZE);
	ft_bzero(vm->colors, MEM_SIZE);
	set_op_tab(vm);
}

void	puthex(char byte)
{
	char		hex[17] = "0123456789abcdef";
	ft_putchar(hex[(byte & 0xf0) >> 4]);
	ft_putchar(hex[(byte & 0x0f)]);
}

void	ft_putarena(unsigned char *arena, int size)
{
	int index;

	index = 0;
	while (index < MEM_SIZE)
	{
		puthex(arena[index]);
		index++;
		if (index % 64 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
}

void	place_player(t_vm *vm, int pnum)
{
	int			i;
	int			ret;
	t_champ		*ch;

	ch = &vm->champs[pnum];
	ch->fd = open(ch->name, O_RDONLY);
	if (ch->fd > 0)
		col_str_fd(FGRN, "champion exists : \n", 1);
	else
		exit(1);
	READ_ERR(ch->fd, ch->magic, 4,"Exec Magic Incomplete");
	READ_ERR(ch->fd, ch->prog_name, PROG_NAME_LENGTH - 4, "Program name err");
	READ_ERR(ch->fd, ch->size, 12, "Invalid program size");
	READ_ERR(ch->fd, ch->prog_comment, COMMENT_LENGTH + 4, "Invalid Comment");
	ch->p_size = (ch->size[11] + ((int)ch->size[10] << 8) + 1);
	ch->core = malloc(sizeof(unsigned char) * ch->p_size);
	i = 0;
	while ((ret = read(ch->fd, ch->core + i, 1)) > 0) {
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
		vm->champs[p].start = vm->champs[p].ldnbr * (MEM_SIZE/vm->num_champs);
		cur = create_cursor(vm->champs[p].start);
		cur->waitcycles = vm->op_tab[vm->arena[cur->pc]].cycles;
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
