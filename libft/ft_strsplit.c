/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:53:23 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/28 14:14:06 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_strsplit(char const *s, char c)
{
	char	**ret;
	char	**str;
	int		nwords;

	if (*s)
	{
		nwords = ft_strwordcnt(s, c);
		if (!(str = (char **)malloc((nwords + 1) * sizeof(char *))))
			return (NULL);
		ret = str;
		while (*s && nwords--)
		{
			while (*s == c)
				s++;
			*str = ft_strwordchr(s, c);
			while (*s && *s != c)
				s++;
			str++;
		}
		*str = NULL;
		return (ret);
	}
	return (NULL);
}
