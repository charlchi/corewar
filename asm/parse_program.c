/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 09:13:40 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/24 12:30:46 by mgerber          ###   ########.fr       */
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
	printf("\n");
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

	startpc = parser->pc - 1;
	if (parser->op_tab[i - 1].acb)
	{
		parse_acb(parser, tokens, i);
	}
	j = 0;
	while (j < parser->op_tab[i - 1].nargs)
	{
		if (tokens[j][0] == 'r')
		{
			add_byte(parser, ft_atoi(&tokens[j][1]));
		}
		else if (tokens[j][0] == DIRECT_CHAR && parser->op_tab[i - 1].label_size == 0)
		{
			if (tokens[j][1] == LABEL_CHAR) // direct label value
			{
				num = get_label_index(parser->list, &tokens[j][2]);
				num = num >= startpc ? num - startpc : 0xffff - (startpc - num) + 1;
				bytestr(parser, num, 4);
			}
			else
			{
				bytestr(parser, ft_atoi(&tokens[j][1]), 4);
			}
		}
		else if (tokens[j][0] == DIRECT_CHAR && parser->op_tab[i - 1].label_size == 1)
		{
			if (tokens[j][1] == LABEL_CHAR) // direct label value
			{
				num = get_label_index(parser->list, &tokens[j][2]);
				num = num >= startpc ? num - startpc : 0xffff - (startpc - num) + 1;
				bytestr(parser, num, 2);
			}
			else
			{
				bytestr(parser, ft_atoi(&tokens[j][1]), 2);
			}
		}
		else if (ft_isdigit(tokens[j][0]) || tokens[j][0] == '-')
		{ // indirect ???
			printf("token indirect %s\n", tokens[j]);
			printf("%d\n", ft_atoi(&tokens[j][0]));
			bytestr(parser, ft_atoi(&tokens[j][0]), 2);
		}
		parser->pc += instruction_val(parser, tokens[j], i - 1);
		j++;
	}
}

void	parse_program(t_parser *parser)
{
	char	**tokens;
	char	*r;
	char	*l;
	int		i;
	//int		currentbyte;

	//currentbyte = 0;
	while ((l = get_asm_line(parser)))
	{
		// replace commas with spaces, then string split
		while ((r = ft_strchr(l, SEPARATOR_CHAR)))
			*r = ' ';
		tokens = ft_strsplit(l, ' ');
		if (ft_strchr(tokens[0], ':')) // TODO: don't skip label
			tokens++;
		if (tokens[0])
		{
			i = 0;
			while (i < 16)
			{
				printf("[%s][%s]", tokens[0], parser->op_tab[i].name);
				if (ft_strequ(tokens[0], parser->op_tab[i].name))
					break ;
				i++;
			}
			printf("%s %d\n", tokens[0], i);
			//There should be a check to see that there was a valid instruction
			add_byte(parser, (char)parser->op_tab[i].id);
			parser->pc++;
			tokens++;
			parse_params(parser, tokens, parser->op_tab[i].id);
		}
	}
	printf("THUAHSDFIHASDIODSHADHIOS\n");
	int test = 0;
	printf("%d\n", parser->pos);
	while (test < parser->pos)
	{
		write(parser->ofd, &parser->program[test++], 1);
	}

}

void	parse_name(t_parser *parser)
{
	char	*l;
	int		i;
	int		j;

	l = get_asm_line(parser);
	printf("%s\n", l);
	if (ft_strncmp(".name", l, 5) != 0)
		asm_parse_err(parser,
			"Expected .name \"championname\"\n");
	i = 8;
	printf("%c\n", l[8]);
	j = 0;
	while (l[i] != '"' && l[i])
	{
		add_byte(parser, l[i++]);
		j++;
	}
	if (j == 0 || l[i] != '"')
		asm_parse_err(parser,
			"Champion .name invalid\nExpected .name \"championname\"\n");
	while (++j <= PROG_NAME_LENGTH - 4)
		add_byte(parser, 0);
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
}

void	parse_champion(char *ifile)
{
	printf("hello\n");
	t_parser	*parser;
	char		*ofile;
	t_labels	*list;
	int			k;

	parser = (t_parser *)malloc(sizeof(t_parser));
	set_op_tab(parser);
	list = NULL;
	ofile = (char *)malloc(ft_strlen(ifile) + 2);
	ft_strcpy(ofile, ifile);
	ft_strcpy(&ofile[ft_strlen(ifile) - 1], "cor");
	if ((parser->ifd = open(ifile, O_RDONLY)) < 0)
		asm_err("Unable to open input file\n");
	if ((parser->ofd = open(ofile, O_RDWR | O_CREAT, 0666)) < 0)
		asm_err("Unable to open output file\n");

	// get rid of name and comment, then get labels
	get_asm_line(parser);
	get_asm_line(parser);
	printf("First pass\n");
	k = first_pass(parser, &list);
	printf("First pass done\n");
	parser->list = list;
	close(parser->ifd);

	// reopen to do the parsing
	if ((parser->ifd = open(ifile, O_RDONLY)) < 0)
		asm_err("Unable to open input file\n");
	parser->line = 0;
	parser->pos = 0;
	parser->pc = 0;
	add_bytes(parser, "\x00\xea\x83\xf3", 4);
	parse_name(parser);
	add_bytes(parser, "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 10);
	bytestr(parser, k, 2);
	parse_comment(parser);
	parse_program(parser);
	free(ofile);
	free(parser);
	close(parser->ifd);
	close(parser->ofd);
}
