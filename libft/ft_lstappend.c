/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 13:24:18 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/24 15:36:19 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **lst, t_list *new)
{
	t_list	*end;

	if (!*lst)
	{
		*lst = new;
	}
	else
	{
		end = *lst;
		while (end->next)
		{
			end = end->next;
		}
		end->next = new;
	}
}
