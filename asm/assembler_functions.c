/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:24:47 by cmoller           #+#    #+#             */
/*   Updated: 2018/12/04 15:24:48 by cmoller          ###   ########.fr       */
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
		FREEIF(array[i++]);
	FREEIF(array);
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
	return (ft_strdup(str + i));
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
