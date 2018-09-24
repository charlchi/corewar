/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 13:21:21 by cmoller           #+#    #+#             */
/*   Updated: 2018/06/01 12:11:29 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dst, const char *src, unsigned int siz)
{
	unsigned int	dlen;
	unsigned int	d;
	unsigned int	s;

	dlen = ft_strlen(dst);
	d = 0;
	s = 0;
	if (dlen > siz)
		return (siz + (unsigned int)ft_strlen(src));
	while (dst[d])
		d++;
	while (src[s] && (int)s < (int)(siz - dlen - 1) && (dst[d] = src[s]))
	{
		d++;
		s++;
	}
	dst[d] = '\0';
	return (dlen + (unsigned int)ft_strlen(src));
}
