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

#define CHECKRETURN(read, str) if((read) < 1)ERROR(str)
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
	int num_players = 0;
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
				vm->champs[num_players].ldnbr = num_players;
				vm->champs[num_players].name = ft_strdup(av[i]);
				ft_putendl_fd(vm->champs[num_players].name, 1);
				num_players++;
				col_str_fd(FGRN, "Valid File\t:\t", 1);
				ft_putendl_fd(av[i], 1);
			}
			close(fd);
		}
		i++;
	}
	vm->num_champs = (num_players <= 4 ? num_players : 0);
}

void	init(t_vm *vm)
{
	vm->num_champs = 0;
	vm->first = NULL;
	ft_bzero(vm->arena, MEM_SIZE);
	set_op_tab(vm);
}

char	*uctohex(int byte)
{
	char	*hex;
	char	*hex_p;
	int		temp;

	hex = "\0\0\0";
	hex_p = hex;
	temp = byte / 16;
	if (temp < 10)
		*hex_p = 48 + temp;
	else
		*hex_p = 55 + 32 + temp;
	hex_p++;
	temp = byte % 16;
	if (temp < 10)
		*hex_p = 48 + temp;
	else
		*hex_p = 55 + 32 + temp;
	return(hex);
}

void	puthex(char byte)
{
	char		hex[20] = "0123456789abcdef";
	ft_putchar(hex[(byte & 0xf0) >> 4]);
	ft_putchar(hex[(byte & 0x0f)]);
}

void	ft_putarena(unsigned char *arena, int size)
{
	int index;

	(void)arena;
	index = 0;
	while (index < size)
	{
		puthex(arena[index]);
		index++;
		if (index % 32 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
}

void	place_player(t_champ *champ, int start, t_vm *vm)
{
	champ->fd = open(champ->name, O_RDONLY);
	if (champ->fd > 0)
	{
		col_str_fd(FGRN, "champion exists : ", 1);
		col_endl_fd(FCYN, champ->name, 1);
	}
	else
		exit(1);
	CHECKRETURN(read(champ->fd, champ->magic, 4),"Magic Invalid");
	CHECKRETURN(read(champ->fd, champ->prog_name, PROG_NAME_LENGTH - 4),
	"Invalid program name");
	CHECKRETURN(read(champ->fd, champ->size, 12), "Invalid program size");
	champ->p_size = (champ->size[11] + ((int)champ->size[10] << 8) + 1);
	CHECKRETURN(read(champ->fd, champ->prog_comment, COMMENT_LENGTH + 4),
	"Invalid Comment");
	champ->core = malloc(sizeof(unsigned char)*champ->p_size);
	CHECKRETURN(read(champ->fd, champ->core, champ->p_size),
	"Invalid instructions");
	ft_memcpy(&vm->arena[start], champ->core, champ->p_size);
	ft_putstr("Loaded player succesfully\n");
}

void	load_vm(t_vm *vm)
{
	int			player;
	t_process	*cursor;

	player = 0;
	while (player < vm->num_champs)
	{
		vm->champs[player].start = vm->champs[player].ldnbr * (MEM_SIZE/vm->num_champs);
		cursor = create_cursor(vm->champs[player].start);

		cursor->waitcycles = vm->op_tab[vm->arena[cursor->pc]].cycles;
		printf("init waitcycles %d\n", cursor->waitcycles);
		add_cursor(vm, cursor);
		place_player(&vm->champs[player], vm->champs[player].start, vm);
		printf("%p\n", cursor);
		printf("testerino makerino, %d, %d\n", cursor->pc, vm->arena[cursor->pc]);
		player++;
	}
	ft_putstr("Done load_vm\n");
}
