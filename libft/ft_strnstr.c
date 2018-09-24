/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 13:01:52 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/27 17:39:51 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned int	i;
	int				f_size;
	int				s;

	i = 0;
	s = 0;
	f_size = ft_strlen(to_find);
	if (f_size == 0)
		return ((char *)str);
	while (i + s < len && str[i])
	{
		while (i + s < len && to_find[s] && str[i + s] == to_find[s])
		{
			if (s == f_size - 1)
				return ((char *)&str[i]);
			s++;
		}
		s = 0;
		i++;
	}
	return (NULL);
}
