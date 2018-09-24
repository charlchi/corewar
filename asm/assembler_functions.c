/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 12:21:16 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/12 15:10:28 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

#include <stdio.h>

void		free_split(char **array)
{
	int i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

char	*strip_asm(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while ((new = ft_strchr(str, '\t')))
		*new = ' ';
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	while (str[j] != COMMENT_CHAR && str[j] != '\0')
		j++;
	j--;
	while (str[j] == ' ')
		j--;
	str[j + 1] = '\0';
	return (str + i);
}

char	*get_asm_line(t_parser *parser)
{
	char	*l;
	char	*asml;
	int		r;

	parser->line++;
	parser->col = 0;
	asml = NULL;
	if ((r = get_next_line(parser->ifd, &l) > 0))
		asml = strip_asm(l);
	while (r > 0 && ft_strlen(asml) == 0)
	{
		parser->line++;
		parser->col = 0;
		r = get_next_line(parser->ifd, &l);
		asml = strip_asm(l);
	}
	return (asml);
}

void	add_bytes(t_parser *parser, char *s, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		parser->program[parser->pos] = (int)(*s++);
		parser->pos++;
		i++;
	}
}

void	add_byte(t_parser *parser, int c)
{
	parser->program[parser->pos] = (int)c;
	parser->pos++;
}