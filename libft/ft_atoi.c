/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:57:49 by cmoller           #+#    #+#             */
/*   Updated: 2018/06/11 13:35:27 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *nptr)
{
	unsigned long	cut;
	unsigned long	n;
	int				neg;

	n = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\v' || *nptr == '\f'
			|| *nptr == '\r' || *nptr == '\n')
		nptr++;
	if (ft_issign(nptr, &neg, &cut))
		nptr++;
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))
	{
		n = n * 10 + ((*nptr++ - '0'));
		if (n > cut || (n == cut && (*nptr - '0') > (int)(cut * 10 % 10)))
		{
			n = LONG_MAX;
			if (neg)
				n = LONG_MIN;
			break ;
		}
	}
	if (neg == 1)
		return ((int)(-n));
	return ((int)n);
}
