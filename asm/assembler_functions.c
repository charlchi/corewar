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

	if (array)
	{
		i = 0;
		while (array[i])
		{
			FREEIF(array[i]);
			i++;
		}
		FREEIF(array);
	}
}

void		add_bytes(t_parser *parser, char *s, int n)
{
	int				i;

	i = 0;
	while (i < n)
	{
		parser->program[parser->pos] = (unsigned char)(*s++);
		parser->pos++;
		i++;
	}
}

void		add_byte(t_parser *parser, int c)
{
	parser->program[parser->pos] = (unsigned char)c;
	parser->pos++;
}

void		free_labels(t_labels **list)
{
	t_labels		*curr;
	t_labels		*next;

	curr = *list;
	while (curr)
	{
		next = curr->next;
		FREEIF(curr->name);
		FREEIF(curr);
		curr = next;
	}
}
