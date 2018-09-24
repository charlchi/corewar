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

	printf("uctoi byte %d", *pos);
	i = 0;
	ret = 0;
	while (++i <= bytes)
		ret += (pos[i] << ((bytes - i) * 8));
	printf("ret %d\n", ret);
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

	k = 0;
	while (k < 16)
	{
		if (vm->op_tab[k].id == c)
			return (c);
		k++;
	}
	return (0);
}

int				consume_param(unsigned char *pos, int *pc, int bytes)
{
	int		ret;

	ret = uctoi(pos + *pc, bytes);
	*pc += bytes;
	return (ret);
}
