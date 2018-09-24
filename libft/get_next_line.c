/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 12:51:45 by cmoller           #+#    #+#             */
/*   Updated: 2018/06/18 15:05:05 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		gnl_strlen(char *src)
{
	int		i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

int		gnl_strccpy(char *src, char *dst, int c)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		if (dst[i] == (char)c)
		{
			dst[i] = 0;
			return (i);
		}
		i++;
	}
	dst[i] = 0;
	return (i);
}

int		gnl_getfdbuff(char **b, const int fd)
{
	static t_fd		*fb[5000];
	int				i;
	int				r;

	i = -1;
	while (fb[++i] != NULL)
		if (fb[i]->fd == fd)
			break ;
	if (fb[i] == NULL)
	{
		if (!(fb[i] = (t_fd *)malloc(sizeof(t_fd))))
			return (-1);
		fb[i]->fd = fd;
		fb[i]->b[0] = 0;
	}
	*b = fb[i]->b;
	if (read(fd, 0, 0) != 0)
		return (-1);
	if ((r = gnl_strlen(&(*b)[0])) == 0)
		if ((r = read(fd, &(*b)[0], BUFF_SIZE)) >= 0)
			(*b)[r] = 0;
	return (r);
}

int		get_next_line(const int fd, char **l)
{
	char			*b;
	int				j;
	int				i;
	int				r;

	if (l == NULL || fd < 0 || BUFF_SIZE < 1)
		return (-1);
	if (!(*l = (char *)malloc(5000000)))
		return (-1);
	r = gnl_getfdbuff(&b, fd);
	(*l)[0] = 0;
	j = 0;
	while (r > 0)
	{
		i = gnl_strlen(*l);
		if (b[(j = gnl_strccpy(b, &(*l)[i], '\n'))] == '\n')
			return (gnl_strccpy(&b[j + 1], &b[0], 0) + 1 > 0);
		if ((r = read(fd, &b[0], BUFF_SIZE)) >= 0)
			b[r] = 0;
	}
	if (j > 0)
		return (1);
	return (r);
}
