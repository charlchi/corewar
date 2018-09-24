/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 13:20:19 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/28 13:00:59 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*next;

	if (*alst)
	{
		curr = *alst;
		while (curr)
		{
			next = curr->next;
			ft_lstdelone(&curr, del);
			curr = next;
		}
	}
	*alst = NULL;
	alst = NULL;
}
