/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:15:13 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/21 14:37:33 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (c == 0)
		return ((char *)&(s[i]));
	i--;
	while (i >= 0)
	{
		if (s[i] == (unsigned char)(c))
			return ((char *)&(s[i]));
		i--;
	}
	return (NULL);
}
