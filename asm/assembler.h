/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:57:38 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/30 16:57:40 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

# include <sys/types.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "op.h"

# define FREEIF(f) if (f) free(f)

typedef struct		s_labels
{
	char			*name;
	int				index;
	struct s_labels	*next;
}					t_labels;

typedef struct		s_parser
{
	t_labels		*list;
	t_op			op_tab[17];
	int				pos;
	int				pc;
	int				start;
	int				ifd;
	int				ofd;
	int				program[8000];
	int				line;
	int				col;
	int				size;
	char			*file;
}					t_parser;

void				free_labels(t_labels **list);
void				bytestr(t_parser *parser, int val, int n);
void				set_op_tab(t_parser *parser);
int					is_label(char *str);
t_labels			*new_label(char *str, int i);
void				add_label(char *str, int i, t_labels **list);
int					get_label_index(t_labels *list, char *label);
int					instruction_val(t_parser *parser, char *str, int k);
int					create_labels(t_parser *p, char *a, int i, t_labels **l);
int					first_pass(t_parser *parser, t_labels **list);
char				*strip_asm(char *str);
char				*get_asm_line(t_parser *parser);
void				add_bytes(t_parser *parser, char *s, int n);
void				add_byte(t_parser *parser, int c);
void				asm_err(char *s);
void				asm_parse_err(t_parser *parser, char *s);
void				parse_acb(t_parser *parser, char **tokens, int i);
void				parse_params(t_parser *parser, char **tokens, int i);
void				parse_program(t_parser *parser);
void				parse_name(t_parser *parser);
void				parse_comment(t_parser *parser);
void				parse_champion(char *ifile);
void				free_split(char **array);

#endif
