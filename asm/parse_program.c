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
	add_byte(parser, (char)opcode);
	parser->pc++;
}

void	parse_params(t_parser *parser, char **tok, int i)
{
	int		n;
	int		j;
	int		s;
	int		size;

	s = parser->pc - 1;
	if (parser->op_tab[i - 1].acb)
		parse_acb(parser, tok, i);
	j = 0;
	while (j < parser->op_tab[i - 1].nargs)
	{
		if (tok[j][0] == 'r')
			add_byte(parser, ft_atoi(&tok[j][1]));
		else if (tok[j][0] == DIRECT_CHAR)
		{
			size = parser->op_tab[i - 1].label_size;
			if (tok[j][1] == LABEL_CHAR)
			{
				n = get_label_index(parser->list, &tok[j][size == 0 ? 4 : 2]);
				n = n >= s ? n - s : 0xffff - (s - n) + 1;
				bytestr(parser, n, size == 0 ? 4 : 2);
			}
			else
			{
				bytestr(parser, ft_atoi(&tok[j][1]), size == 0 ? 4 : 2);
			}
		}
		else if (ft_isdigit(tok[j][0]) || tok[j][0] == '-')
			bytestr(parser, ft_atoi(&tok[j][0]), 2);
		parser->pc += instruction_val(parser, tok[j], i - 1);
		j++;
	}
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
		if (ft_strchr(tok[0], ':'))
			tok++;
		if (tok[0])
		{
			i = -1;
			while (++i < 16)
				if (ft_strequ(tok[0], parser->op_tab[i].name))
					break ;
			add_byte(parser, (char)parser->op_tab[i].id);
			parser->pc++;
			tok++;
			parse_params(parser, tok, parser->op_tab[i].id);
		}
		free_split(freetok);
		free(l);
	}
}

void	parse_name(t_parser *parser)
{
	char	*l;
	int		i;
	int		spaces;

	l = get_asm_line(parser);
	if (l == NULL)
		asm_parse_err(parser, ".name bad format\n");
	if (ft_strncmp(".name \"", l, 7) != 0)
		asm_parse_err(parser, ".name bad format\n");
	i = 7;
	spaces = 0;
	while (l[i] != '"' && l[i])
	{
		add_byte(parser, l[i++]);
		spaces++;
	}
	if (spaces == 0 || l[i] != '"')
		asm_parse_err(parser, ".name bad format\n");
	while (++spaces <= PROG_NAME_LENGTH - 4)
		add_byte(parser, 0);
	free(l);
}

void	parse_comment(t_parser *parser)
{
	char	*l;
	int		i;
	int		j;

	l = get_asm_line(parser);
	if (ft_strncmp(".comment", l, 8) != 0)
		asm_parse_err(parser, "Champion .comment not found");
	i = 8;
	while (l[i] == ' ')
		i++;
	j = 0;
	while (l[++i] != '"')
	{
		add_byte(parser, l[i]);
		j++;
	}
	while (++j <= COMMENT_LENGTH + 4)
		add_byte(parser, 0);
	free(l);
}

void	open_champ_files(t_parser *parser, char *ifile)
{
	char		*ofile;

	ofile = (char *)malloc(ft_strlen(ifile) + 2);
	ft_strcpy(ofile, ifile);
	ft_strcpy(&ofile[ft_strlen(ifile) - 1], "cor");
	if ((parser->ifd = open(ifile, O_RDONLY)) < 0)
		asm_err("Unable to open input file\n");
	if ((parser->ofd = open(ofile, O_RDWR | O_CREAT, 0666)) < 0)
		asm_err("Unable to open output file\n");
	free(ofile);
}

void	parse_champion(char *ifile)
{
	int			i;
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	set_op_tab(parser);
	parser->list = NULL;
	open_champ_files(parser, ifile);
	parser->size = first_pass(parser, &parser->list);
	lseek(parser->ifd, 0, SEEK_SET);
	parser->line = 0;
	parser->pos = 0;
	parser->pc = 0;
	add_bytes(parser, "\x00\xea\x83\xf3", 4);
	parse_name(parser);
	add_bytes(parser, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 10);
	bytestr(parser, parser->size, 2);
	parse_comment(parser);
	parse_program(parser);
	i = 0;
	while (i < parser->pos)
		write(parser->ofd, &parser->program[i++], 1);
	free(parser);
	close(parser->ifd);
	close(parser->ofd);
}
