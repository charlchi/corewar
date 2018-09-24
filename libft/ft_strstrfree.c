/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:57:49 by cmoller           #+#    #+#             */
/*   Updated: 2018/07/26 13:46:33 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_strstrfree(char **strstr)
{
	int		i;

	if (strstr)
	{
		i = 0;
		while (strstr[i])
		{
			free(strstr[i]);
			i++;
		}
		free(strstr);
	}
}
