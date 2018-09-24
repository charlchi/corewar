/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 16:53:52 by cmoller           #+#    #+#             */
/*   Updated: 2018/05/21 15:13:29 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*newstr;
	char	*start;

	if (!(newstr = (char *)malloc(size + 1)))
		return (NULL);
	start = newstr;
	while (size--)
		*newstr++ = '\0';
	*newstr = '\0';
	return (start);
}
