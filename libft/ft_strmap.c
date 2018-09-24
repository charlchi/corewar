/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 17:03:55 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/28 14:03:29 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*ret;
	char	*newstr;

	if (s && f)
	{
		if (!(newstr = (char *)malloc(ft_strlen(s) + 1)))
			return (NULL);
		ret = newstr;
		while (*s)
		{
			*newstr = f(*s);
			newstr++;
			s++;
		}
		*newstr = '\0';
		return (ret);
	}
	return (NULL);
}
