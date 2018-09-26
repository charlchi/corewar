/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 09:11:05 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/21 09:16:35 by mgerber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	uctoi(unsigned char *pos, int bytes)
{
	int				i;
	unsigned int	ret;

	ret = pos[0];
	i = 1;
	while (i < bytes)
	{
		ret = ret << 8;
		ret += pos[i];
		i++;
	}
	return (ret);
}

void			itouc(unsigned char *pos, unsigned int num)
{
	pos[0] = (num & 0xff000000) >> 24;
	pos[1] = (num & 0x00ff0000) >> 16;
	pos[2] = (num & 0x0000ff00) >> 8;
	pos[3] = (num & 0x000000ff);
}

int				is_action(t_vm *vm, unsigned char c)
{
	int k;

	if (c >= 1 && c <= 16)
		return (c);
	return (0);
}

unsigned int		consume_param(unsigned char *pos, int *pc, int bytes)
{
	unsigned int		ret;

	ret = uctoi(pos + *pc, bytes);
	*pc += bytes;
	return (ret);
}

char	*acb_to_chars(unsigned char *mem, unsigned char *acb)
{
	acb[0] = (*mem) & 0b11000000;
	acb[1] = (*mem) & 0b00110000;
	acb[2] = (*mem) & 0b00001100;
	acb[3] = 0;
}