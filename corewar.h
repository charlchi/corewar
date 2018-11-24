/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 11:28:36 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/21 09:22:19 by mgerber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <curses.h> 
# include "libft/libft.h"
# include "op.h"
# include <stdlib.h>
# include <stdio.h>

# define BITS(x) {  printf("%d", x & 128 ? 1: 0);\
					printf("%d", x & 64 ? 1: 0);\
					printf("%d", x & 32 ? 1: 0);\
					printf("%d", x & 16 ? 1: 0);\
					printf("%d", x & 8 ? 1: 0);\
					printf("%d", x & 4 ? 1: 0);\
					printf("%d", x & 2 ? 1: 0);\
					printf("%d", x & 1 ? 1: 0);\
					printf("\n");}
# define MEM(x) (x >= 0 ? (x % MEM_SIZE) : (MEM_SIZE - (abs(x) % MEM_SIZE)))
# define IDX(x) (x >= 0 ? (x % IDX_MOD) : -((abs(x) % IDX_MOD)))

typedef struct		s_process
{
	int				start;
	int				is_reg[3];
	int				params[3];
	int				waitcycles;
	int				live_flag;
	int				dead_flag;
	int				pc;
	int				carry;
	int				reg[REG_NUMBER];
	void			*next;
}					t_process;


typedef struct  	s_champ
{
    unsigned char	prog_name[PROG_NAME_LENGTH+4];
	unsigned char	prog_comment[COMMENT_LENGTH+4];
	unsigned char	size[12];
	unsigned char	*core;
	unsigned char	magic[4];
	char			*name;
	int				ldnbr;
    unsigned int	number;
	int				start_index;
	int				lives;
	int				last_live;
	int				fd;
	int				start;
	int				p_size;
}					t_champ;

typedef struct		s_vm
{
	t_op			op_tab[17];
	unsigned char	arena[MEM_SIZE];
	unsigned char	colors[MEM_SIZE];
	int				num_champs;
	t_champ			champs[MAX_PLAYERS];
	t_process		*first;
	int				total_cycles;
	int				cycle;
	int				cycle_to_die;
	int				lives;
}					t_vm;

void				print_vm(t_vm *vm);
void				run_vm(t_vm *vm);
void				add_cursor(t_vm *vm, t_process *cursor);
int					living_cursors(t_vm *vm);
void				kill_cursors(t_vm *vm);
void				execute_process(t_vm *vm, t_process *cursor);
t_process			*create_cursor(int i);
t_process			*clone_cursor(t_process *orig, int pc);
void				cw_live(t_vm *vm, t_process *cursor);
void				cw_ld(t_vm *vm, t_process *cursor);
void				cw_st(t_vm *vm, t_process *cursor);
void				cw_add(t_vm *vm, t_process *cursor);
void				cw_sub(t_vm *vm, t_process *cursor);
void				cw_and(t_vm *vm, t_process *cursor);
void				cw_or(t_vm *vm, t_process *cursor);
void				cw_xor(t_vm *vm, t_process *cursor);
void				cw_zjmp(t_vm *vm, t_process *cursor);
void				cw_ldi(t_vm *vm, t_process *cursor);
void				cw_sti(t_vm *vm, t_process *cursor);
void				cw_fork(t_vm *vm, t_process *cursor);
void				cw_lld(t_vm *vm, t_process *cursor);
void				cw_lldi(t_vm *vm, t_process *cursor);
void				cw_lfork(t_vm *vm, t_process *cursor);
void				cw_aff(t_vm *vm, t_process *cursor);
int					is_action(t_vm *vm, unsigned char c);
void				col_endl_fd(char *colour, char *str, int fd);
void				col_char_fd(char *colour, char c, int fd);
void				col_str_fd(char *colour, char *str, int fd);
void				ft_nbrendl_fd(int nbr, int fd);
void				ft_nbrendl(int nbr);
void				ft_putarr_fd(char **arr, int fd);
int					ft_contains(char *whole, char *part);
void 				count_champs(t_vm *vm, int ac, char **av);
void				init(t_vm *vm);
void				puthex(char byte);
void				ft_putarena(unsigned char *arena, int size);
void				place_player(t_vm *vm, int pnum);
void				load_vm(t_vm *vm);
void				set_op_tab(t_vm *vm);

int					check_args(t_vm *vm, t_op *op, t_process *cursor);
int					check_args_nocode(t_vm *vm, t_op *op, t_process *cursor);
int					code_size(int code, int label_size);
int					read_arg(t_vm *vm, int pos, int code, int label_size);

#endif
