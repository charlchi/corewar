/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:38:32 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/24 16:38:39 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include <stdio.h>

void		bytestr(t_parser *parser, int val, int n)
{
	int				i;
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

void		free_split(char **array)
{
	int				i;

	i = 0;
	while (array && array[i])
		free(array[i++]);
	free(array);
}

char		*strip_asm(char *str)
{
	int				i;
	int				j;
	char			*new;

	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if ((new = ft_strchr(str, COMMENT_CHAR)))
		*new = '\0';
	while ((new = ft_strchr(str, '\t')))
		*new = ' ';
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	while (str[j] != '\0')
		j++;
	j--;
	while (str[j] == ' ')
		j--;
	str[j + 1] = '\0';
	printf("stripped line [%s]\n", str + i);
	return (ft_strdup(str + i));
}

int			get_line(int fd, char **l)
{
	char			buf[1000];
	int				i;
	int				r;

	ft_bzero(buf, 1000);
	i = 0;
	r = 0;
	while ((r = read(fd, &buf[i], 1)) == 1)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			*l = ft_strdup(buf);
			printf("line[%s]\n", *l);
			return (1);
		}
		i++;
	}
	if (i > 0)
	{
		buf[i] = '\0';
		*l = ft_strdup(buf);
		printf("line[%s]\n", *l);
		return (1);
	}
	*l = NULL;
	return (0);
}

char		*get_asm_line(t_parser *parser)
{
	char			*l;
	char			*asml;
	int				r;

	parser->line++;
	parser->col = 0;
	asml = NULL;
	if ((r = get_line(parser->ifd, &l) > 0))
	{
		asml = strip_asm(l);
		free(l);
	}
	while (r > 0 && ft_strlen(asml) == 0)
	{
		free(asml);
		parser->line++;
		parser->col = 0;
		r = get_line(parser->ifd, &l);
		asml = strip_asm(l);
		free(l);
	}
	return (asml);
}

void		add_bytes(t_parser *parser, char *s, int n)
{
	int				i;

	i = 0;
	while (i < n)
	{
		parser->program[parser->pos] = (int)(*s++);
		parser->pos++;
		i++;
	}
}

void		add_byte(t_parser *parser, int c)
{
	parser->program[parser->pos] = (int)c;
	parser->pos++;
}
