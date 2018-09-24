/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 09:13:40 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/12 12:33:53 by mgerber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	asm_err(char *s)
{
	ft_putstr("Error: ");
	ft_putstr(s);
	exit(0);
}

void	asm_parse_err(t_parser *parser, char *s)
{
	ft_putstr("Error line ");
	ft_putnbr(parser->line);
	ft_putstr(": ");
	ft_putstr(s);
	exit(0);
}