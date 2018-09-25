/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 09:13:40 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/25 12:38:03 by mgerber          ###   ########.fr       */
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

void	bytestr(t_parser *parser, int val, int n)
{
	int		i;
	unsigned int	shifted;

	i = n;
	while (i > 0)
	{
		shifted = 0xff << (8 * (i - 1));
		shifted = shifted & val;
		shifted = shifted >> (8 * (i - 1));
		add_byte(parser, shifted);
		i--;
	}
}

void	parse_params(t_parser *parser, char **tokens, int i)
{
	int		num;
	int		j;
	int		startpc;
	int		size;

	startpc = parser->pc - 1;
	if (parser->op_tab[i - 1].acb)
		parse_acb(parser, tokens, i);
	j = 0;
	while (j < parser->op_tab[i - 1].nargs)
	{
		if (tokens[j][0] == 'r')
			add_byte(parser, ft_atoi(&tokens[j][1]));
		else if (tokens[j][0] == DIRECT_CHAR)
		{
			size = parser->op_tab[i - 1].label_size;
			if (tokens[j][1] == LABEL_CHAR) // direct label value
			{
				num = get_label_index(parser->list, &tokens[j][size == 0 ? 4 : 2]);
				num = num >= startpc ? num - startpc : 0xffff - (startpc - num) + 1;
				bytestr(parser, num, size == 0 ? 4 : 2);
			}
			else
			{
				bytestr(parser, ft_atoi(&tokens[j][1]), size == 0 ? 4 : 2);
			}
		}
		else if (ft_isdigit(tokens[j][0]) || tokens[j][0] == '-')
			bytestr(parser, ft_atoi(&tokens[j][0]), 2);
		parser->pc += instruction_val(parser, tokens[j], i - 1);
		j++;
	}
}

void	parse_program(t_parser *parser)
{
	char	**tokens;
	char	**freetok;
	char	*r;
	char	*l;
	int		i;

	while ((l = get_asm_line(parser)))
	{
		while ((r = ft_strchr(l, SEPARATOR_CHAR)))
			*r = ' ';
		tokens = ft_strsplit(l, ' ');
		freetok = tokens;
		if (ft_strchr(tokens[0], ':')) // TODO: don't skip label
			tokens++;
		if (tokens[0])
		{
			i = -1;
			while (++i < 16)
				if (ft_strequ(tokens[0], parser->op_tab[i].name))
					break ;
			add_byte(parser, (char)parser->op_tab[i].id);
			parser->pc++;
			tokens++;
			parse_params(parser, tokens, parser->op_tab[i].id);
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


/*

##	OURS:
##	0b 68 01 0078 0001
##	0b 68 01 0045 0001
##	02 90 00000001 03
##	02 90 00000021 06
##	04 54 02 03 02
##	08 64 02 0000000f 04
##	01 00000004
##	09 003d
##	0c 0001
##	02 90 00000000 04
##	09 fff7
##	02 90 00000000 04
##	01 00000004
##	09 002e
##
##	
##	THEIRS:
##	0b 68 01 0045 0001 
##	0b 68 01 0022 0001 
##	02 90 00000001 03 
##	02 90 00000021 06
##	04 54 02 03 02
##	08 64 02 0000000f 04
##	01 00000004
##	09 0010
##	0c ffeb
##	02 90 00000000 04
##	09 ffe1
##	02 90 00000000 04
##	01 00000004
##	09 fffb
*/