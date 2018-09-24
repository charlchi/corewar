/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 17:14:54 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/28 14:14:48 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char				*str;
	unsigned int		i;

	if (s)
	{
		if (!(str = (char *)malloc(len + 1)))
			return (NULL);
		i = 0;
		while (i < len)
		{
			str[i] = s[i + start];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
