/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 14:43:11 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/28 12:34:48 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dmem;
	unsigned char	*smem;

	dmem = (unsigned char *)dst;
	smem = (unsigned char *)src;
	while (n--)
	{
		*dmem++ = *smem;
		if ((*smem++) == (unsigned char)(c))
			return ((void *)dmem);
	}
	return (NULL);
}
