/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 10:51:53 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/25 10:42:46 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(int c)
{
	if (c <= 0x7F)
	{
		ft_putbyte_fd(c, 1);
	}
	else if (c <= 0x7FF)
	{
		ft_putbyte_fd(0xC0 | (c >> 6), 1);
		ft_putbyte_fd(0x80 | (c & 0x3F), 1);
	}
	else if (c <= 0xFFFF)
	{
		ft_putbyte_fd(0xE0 | (c >> 12), 1);
		ft_putbyte_fd(0x80 | ((c >> 6) & 0x3F), 1);
		ft_putbyte_fd(0x80 | (c & 0x3F), 1);
	}
	else if (c <= 0x10FFFF)
	{
		ft_putbyte_fd(0xF0 | (c >> 18), 1);
		ft_putbyte_fd(0x80 | ((c >> 12) & 0x3F), 1);
		ft_putbyte_fd(0x80 | ((c >> 6) & 0x3F), 1);
		ft_putbyte_fd(0x80 | (c & 0x3F), 1);
	}
}
