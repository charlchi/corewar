/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 09:23:47 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/23 15:45:36 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_issign(const char *nptr, int *neg, unsigned long *cutoff)
{
	*neg = 0;
	*cutoff = LONG_MAX / 10;
	if (*nptr == '-')
	{
		*cutoff = (-(unsigned long)LONG_MIN) / 10;
		*neg = 1;
		return (1);
	}
	else if (*nptr == '+')
		return (1);
	return (0);
}
