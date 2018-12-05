/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:25:31 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/24 16:25:41 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	int		a;
	int		i;

	a = 1;
	while (a < argc)
	{
		if ((i = ft_strlen(argv[a])) < 3)
			asm_err("Invalid file name");
		if (argv[a][i - 1] != 's' || argv[a][i - 2] != '.')
			asm_err("Invalid file extension, must end with \".s\"");
		parse_champion(argv[a]);
		a++;
	}
	return (0);
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
	FREEIF(l);
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
	FREEIF(l);
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
	FREEIF(ofile);
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
	FREEIF(parser);
	close(parser->ifd);
	close(parser->ofd);
}
