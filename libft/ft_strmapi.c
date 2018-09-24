/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 17:07:32 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/28 14:04:00 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	char			*newstr;
	unsigned int	i;

	if (s && f)
	{
		if (!(newstr = (char *)malloc(ft_strlen(s) + 1)))
			return (NULL);
		ret = newstr;
		i = 0;
		while (*s)
		{
			*newstr = f(i, *s);
			newstr++;
			s++;
			i++;
		}
		*newstr = '\0';
		return (ret);
	}
	return (NULL);
}
