/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 11:00:15 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/25 10:42:58 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putchar_fd(int c, int fd)
{
	if (c <= 0x7F)
	{
		ft_putbyte_fd(c, fd);
	}
	else if (c <= 0x7FF)
	{
		ft_putbyte_fd(0xC0 | (c >> 6), fd);
		ft_putbyte_fd(0x80 | (c & 0x3F), fd);
	}
	else if (c <= 0xFFFF)
	{
		ft_putbyte_fd(0xE0 | (c >> 12), fd);
		ft_putbyte_fd(0x80 | ((c >> 6) & 0x3F), fd);
		ft_putbyte_fd(0x80 | (c & 0x3F), fd);
	}
	else if (c <= 0x10FFFF)
	{
		ft_putbyte_fd(0xF0 | (c >> 18), fd);
		ft_putbyte_fd(0x80 | ((c >> 12) & 0x3F), fd);
		ft_putbyte_fd(0x80 | ((c >> 6) & 0x3F), fd);
		ft_putbyte_fd(0x80 | (c & 0x3F), fd);
	}
}
