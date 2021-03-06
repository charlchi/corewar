/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwordchr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 10:13:52 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/18 10:17:18 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strwordchr(char const *s, char c)
{
	char	*ret;
	int		len;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	if (len == 0)
		return (NULL);
	if (!(ret = (char *)malloc(len + 1)))
		return (NULL);
	ret[len] = '\0';
	while (len--)
	{
		ret[len] = s[len];
	}
	return (ret);
}
