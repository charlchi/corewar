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

#ifdef __linux__
# include <GL/gl.h>
# include <GL/glut.h>
# include <GL/glu.h>
#endif

#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#endif

//#pragma clang diagnostic ignored "-Wdeprecated-declarations"

# include "libft/libft.h"
# include "op.h"
# include <stdlib.h>
# include <stdio.h>

typedef struct		s_process
{
	int				waitcycles;
	int				live_flag;
	int				dead_flag;
	int				pc;
	int				carry;
	unsigned int	reg[REG_NUMBER];
	void			*next;
}					t_process;


typedef struct  	s_champ
{
    unsigned char	prog_name[PROG_NAME_LENGTH+5];
	unsigned char	prog_comment[COMMENT_LENGTH+5];
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
	int				pixels[64 * 64];
	t_op			op_tab[16];
	unsigned char	arena[MEM_SIZE];
	int				num_champs;
	t_champ			champs[MAX_PLAYERS];
	t_process		*first;
	int				total_cycles;
	int				cycle;
	int				cycle_to_die;
	int				lives;
}					t_vm;

int					check_acb(t_vm *vm, char opcode, char acb);
int					vm_read_params(t_vm *v, int *c, unsigned int *p, char a);
unsigned int		vm_read(t_vm *vm, int *pos, int n);
void				vm_write(t_vm *vm, int pos, int val, int n);
void				run_vm(void);
void				add_cursor(t_vm *vm, t_process *cursor);
int					living_cursors(t_vm *vm);
void				kill_cursors(t_vm *vm);
void				execute_process(t_vm *vm, t_process *cursor);
t_process			*create_cursor(int i);
t_process			*clone_cursor(t_process *orig, int pc);
void				cw_live(t_vm *vm, t_process *cursor, int start);
void				cw_ld(t_vm *vm, t_process *cursor, int start);
void				cw_st(t_vm *vm, t_process *cursor, int start);
void				cw_add(t_vm *vm, t_process *cursor, int start);
void				cw_sub(t_vm *vm, t_process *cursor, int start);
void				cw_and(t_vm *vm, t_process *cursor, int start);
void				cw_or(t_vm *vm, t_process *cursor, int start);
void				cw_xor(t_vm *vm, t_process *cursor, int start);
void				cw_zjmp(t_vm *vm, t_process *cursor, int start);
void				cw_ldi(t_vm *vm, t_process *cursor, int start);
void				cw_sti(t_vm *vm, t_process *cursor, int start);
void				cw_fork(t_vm *vm, t_process *cursor, int start);
void				cw_lld(t_vm *vm, t_process *cursor, int start);
void				cw_lldi(t_vm *vm, t_process *cursor, int start);
void				cw_lfork(t_vm *vm, t_process *cursor, int start);
void				cw_aff(t_vm *vm, t_process *cursor, int start);
unsigned int		uctoi(unsigned char *pos, int bytes);
void				itouc(unsigned char *pos, unsigned int num);
int					is_action(t_vm *vm, unsigned char c);
unsigned int		consume_param(unsigned char *pos, int *pc, int bytes);
void				col_endl_fd(char *colour, char *str, int fd);
void				col_char_fd(char *colour, char c, int fd);
void				col_str_fd(char *colour, char *str, int fd);
void				ft_nbrendl_fd(int nbr, int fd);
void				ft_nbrendl(int nbr);
void				ft_putarr_fd(char **arr, int fd);
int					ft_contains(char *whole, char *part);
void 				count_champs(t_vm *vm, int ac, char **av);
void				init(t_vm *vm);
char				*uctohex(int byte);
void				puthex(char byte);
void				ft_putarena(unsigned char *arena, int size);
void				place_player(t_champ *champ, int start, t_vm *vm);
void				load_vm(t_vm *vm);
void				set_op_tab(t_vm *vm);

#endif
