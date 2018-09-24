/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 09:39:51 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/28 14:03:01 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		stt;
	int		end;
	char	*str;
	char	*ret;

	if (s)
	{
		stt = 0;
		end = 0;
		while (ft_iswhite(s[stt]))
			stt++;
		while (s[end])
			end++;
		end--;
		while ((stt <= end) && ft_iswhite(s[end]))
			end--;
		if (!(str = (char *)malloc((end + 1) - stt + 1)))
			return (NULL);
		ret = str;
		while (stt <= end)
			*str++ = s[stt++];
		*str = '\0';
		return (ret);
	}
	return (NULL);
}
