/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:27:03 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/24 16:27:05 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include <stdio.h>

int			is_label(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	return ((i > 0 && str[i - 1] == ':') ? 1 : 0);
}

int			instruction_val(t_parser *parser, char *str, int k)
{
	if (str[0] == 'r')
		return (1);
	if (str[0] == '%')
		return (parser->op_tab[k].label_size ? DIR_SIZE / 2 : DIR_SIZE);
	return (IND_SIZE);
}
