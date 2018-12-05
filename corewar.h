/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:02:44 by cmoller           #+#    #+#             */
/*   Updated: 2018/12/04 15:02:46 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <curses.h>
# include "libft/libft.h"
# include "op.h"
# include <stdlib.h>
# include <stdio.h>

# define MEM(x) ((x) >= 0 ? ((x) % MEM_SIZE) : (MEM_SIZE - (abs(x) % MEM_SIZE)))
# define IDX(x) ((x) >= 0 ? ((x) % IDX_MOD) : -((abs(x) % IDX_MOD)))
# define DPRINT(x, ...) ((vm->v & 1) ? printf(x, ##__VA_ARGS__) : 0)

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
	int				n;
}					t_process;

typedef struct		s_champ
{
	unsigned char	prog_name[PROG_NAME_LENGTH + 4];
	unsigned char	prog_comment[COMMENT_LENGTH + 4];
	unsigned char	size[12];
	unsigned char	*core;
	unsigned char	magic[4];
	char			*path;
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
	int				checks;
	int				lives;
	int				v;
	int				dump;
	int				nolive;
	int				last_livep;
	int				n;
}					t_vm;

void				print_usage(void);
void				init_viz(void);
void				print_arena(t_vm *vm);
void				print_cursors(t_vm *vm);
void				print_info(t_vm *vm);
void				print_vm(t_vm *vm);
void				run_vm(t_vm *vm);
void				execute_process(t_vm *vm, t_process *cursor);
void				dump_vm(t_vm *vm);
t_process			*create_cursor(int i);
t_process			*clone_cursor(t_process *orig, int pc);
void				add_cursor(t_vm *vm, t_process *new);
void				clear_cursor_params(t_process *cursor);
void				kill_cursors(t_vm *vm);
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
int					check_args_nocode(t_vm *vm, t_op *op, t_process *cursor);
int					check_args(t_vm *vm, t_op *op, t_process *cursor);
int					code_size(int code, int label_size);
int					read_arg(t_vm *vm, int pos, int code, int label_size);
int					ft_contains(char *whole, char *part);
void				load_champs(t_vm *vm, int ac, char **av);
void				init_vm(t_vm *vm);
void				ft_putarena(unsigned char *arena, int size);
void				place_player(t_vm *vm, int pnum);
void				load_vm(t_vm *vm);
void				set_op_tab(t_vm *vm);

#endif
