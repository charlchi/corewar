/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 12:49:11 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/21 12:55:47 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void			*ret;
	unsigned char	*mem;

	ret = b;
	mem = (unsigned char *)b;
	while (len--)
		*mem++ = (unsigned char)c;
	return (ret);
}
