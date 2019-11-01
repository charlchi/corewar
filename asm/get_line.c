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
		asml = strip_asm(l);
	while (r > 0 && (asml == NULL || ft_strlen(asml) == 0))
	{
		parser->line++;
		parser->col = 0;
		FREEIF(l);
		FREEIF(asml);
		r = get_line(parser->ifd, &l);
		asml = strip_asm(l);
	}
	FREEIF(l);
	return (asml);
}

char		*strip_asm(char *str)
{
	char			*new;

	if (str == NULL || ft_strlen(str) == 0)
		return (NULL);
	// Look for comment char replace with null
	// This potentially cuts off string and puts length at 0
	while ((new = ft_strchr(str, COMMENT_CHAR)))
		*new = '\0';
	// Look for comment char replace with null
	// This potentially cuts off string and puts length at 0
	while ((new = ft_strchr(str, ';')))
		*new = '\0';
	// Replace tabs with spaces
	while ((new = ft_strchr(str, '\t')))
		*new = ' ';
	return ft_strtrim(str);
}
