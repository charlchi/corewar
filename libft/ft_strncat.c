/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 12:31:30 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/28 09:49:04 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *dest, const char *src, size_t n)
{
	int s;
	int d;

	s = 0;
	d = 0;
	while (dest[d])
		d++;
	while (n > 0 && (dest[d] = src[s]))
	{
		d++;
		s++;
		n--;
	}
	if (n == 0)
		dest[d] = '\0';
	return (dest);
}
