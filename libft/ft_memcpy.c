/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 13:03:48 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/21 13:08:51 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dmem;
	unsigned char	*smem;
	void			*ret;

	dmem = (unsigned char *)dst;
	smem = (unsigned char *)src;
	ret = dst;
	while (n--)
		*dmem++ = *smem++;
	return (ret);
}
