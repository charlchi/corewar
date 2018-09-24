/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 13:01:52 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/21 14:45:46 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int		fsize;
	int		i;
	int		s;

	i = 0;
	s = 0;
	fsize = ft_strlen(to_find);
	if (fsize == 0)
		return ((char *)str);
	while (str[i])
	{
		while (str[i + s] == to_find[s])
		{
			if (s == fsize - 1)
				return ((char *)&str[i]);
			s++;
		}
		s = 0;
		i++;
	}
	return (NULL);
}
