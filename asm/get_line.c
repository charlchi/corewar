/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c.                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:38:32 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/24 16:38:39 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include <stdio.h>

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
			return (1);
		}
		i++;
	}
	if (i > 0)
	{
		buf[i] = '\0';
		*l = ft_strdup(buf);
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
		FREEIF(l);
	}
	while (r > 0 && ft_strlen(asml) == 0)
	{
		FREEIF(asml);
		parser->line++;
		parser->col = 0;
		r = get_line(parser->ifd, &l);
		asml = strip_asm(l);
		FREEIF(l);
	}
	return (asml);
}
