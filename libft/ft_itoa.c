/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 10:24:53 by cmoller           #+#    #+#             */
/*   Updated: 2018/06/01 14:40:47 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int val)
{
	long	n;
	char	*str;
	char	*ret;
	int		sign;

	n = (long)val;
	if (!(str = ft_strnew(ft_countint(n))))
		return (NULL);
	ret = str;
	if ((sign = n) < 0)
		n *= -1;
	*str++ = (n % 10) + '0';
	n /= 10;
	while (n > 0)
	{
		*str++ = (n % 10) + '0';
		n /= 10;
	}
	if (sign < 0)
		*str++ = '-';
	*str = '\0';
	ft_strrev(&ret);
	return (ret);
}
