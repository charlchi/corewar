/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 13:50:29 by tpitout           #+#    #+#             */
/*   Updated: 2018/09/20 10:13:48 by mgerber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process		*create_cursor(int i)
{
	int			k;
	t_process	*newcursor;


	newcursor = malloc(sizeof(t_process));
	if (newcursor == NULL)
		return (NULL);
	newcursor->waitcycles = 0;
	newcursor->live_flag = 0;
	newcursor->dead_flag = 0;
	newcursor->pc = i;
	newcursor->carry = 0;
	newcursor->next = NULL;
	newcursor->prev = NULL;
	k = -1;
	while (++k < REG_NUMBER)
		newcursor->reg[k] = 0;
//	newcursor->player =
//	newcursor->dead = 
//	newcursor->color = 
//	newcursor->index = 
	return (newcursor);
}

t_process		*clone_cursor(t_process *orig, int pc)
{
	t_process	*clone;

	clone = malloc(sizeof(t_process));
	ft_memcpy((char *)clone, (char *)orig, sizeof(t_process));
	// confirm that this ^^ works plz
	clone->pc = pc;
	clone->next = NULL;
	return (clone);
}
