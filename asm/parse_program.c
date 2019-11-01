/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:26:42 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/24 16:26:44 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include <stdio.h>

void	parse_acb(t_parser *parser, char **tokens, int i)
{
	int		j;
	int		k;
	int		opcode;

	opcode = 0;
	j = 0;
	k = 3;
	while (j < parser->op_tab[i - 1].nargs)
	{
		if (tokens[j][0] == 'r')
			opcode += (1 << (k * 2));
		else if (tokens[j][0] == DIRECT_CHAR)
			opcode += (2 << (k * 2));
		else
			opcode += (3 << (k * 2));
		j++;
		k--;
	}
	if (tokens[j] != NULL)
		asm_parse_err(parser, "Invalid number of arguments!\n");
	add_byte(parser, (char)opcode);
	parser->pc++;
}

void	parse_direct(t_parser *p, char **tok, int j, int i)
{
	int		n;
	int		s;
	int		size;

	s = p->start - 1;
	size = p->op_tab[i - 1].label_size;
	if (tok[j][1] == LABEL_CHAR)
	{
		n = get_label_index(p->list, &tok[j][size == 0 ? 4 : 2]);
		n = n >= s ? n - s : 0xffff - (s - n) + 1;
		bytestr(p, n, size == 0 ? 4 : 2);
	}
	else if (ft_isdigit(tok[j][1]) || tok[j][1] == '-')
		bytestr(p, ft_atoi(&tok[j][1]), size == 0 ? 4 : 2);
}

void	parse_params(t_parser *p, char **tok, int i)
{
	int		j;
	int		val;

	(p->op_tab[i - 1].acb ? parse_acb(p, tok, i) : 0);
	j = -1;
	while (++j < p->op_tab[i - 1].nargs)
	{
		if (tok[j][0] == 'r')
		{
			val = ft_atoi(&tok[j][1]);
			if (val <= 0 || val > 16)
				asm_parse_err(p, "Invalid register size\n");
			add_byte(p, val);
		}
		else if (tok[j][0] == DIRECT_CHAR)
			parse_direct(p, tok, j, i);
		else if (ft_isdigit(tok[j][0]) || tok[j][0] == '-')
			bytestr(p, ft_atoi(&tok[j][0]), 2);
		else
			asm_parse_err(p, "Invalid parameters\n");
		p->pc += instruction_val(p, tok[j], i - 1);
	}
}

int		get_index(t_parser *parser, char *tok)
{
	int		i;

	i = -1;
	while (++i < 16)
		if (ft_strequ(tok, parser->op_tab[i].name))
			return (i);
	return (0);
}

void	parse_program(t_parser *parser)
{
	char	**tok;
	char	**freetok;
	char	*r;
	char	*l;
	int		i;

	while ((l = get_asm_line(parser)))
	{
		while ((r = ft_strchr(l, SEPARATOR_CHAR)))
			*r = ' ';
		tok = ft_strsplit(l, ' ');
		freetok = tok;
		tok += ft_strchr(tok[0], ':') ? 1 : 0;
		if (tok && tok[0])
		{
			i = get_index(parser, tok[0]);
			add_byte(parser, (char)parser->op_tab[i].id);
			parser->pc++;
			parser->start = parser->pc;
			tok++;
			parse_params(parser, tok, parser->op_tab[i].id);
		}
		free_split(freetok);
		FREEIF(l);
	}
}
