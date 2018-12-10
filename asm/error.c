/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:26:26 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/24 16:26:29 by cmoller          ###   ########.fr       */
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
	ft_putstr(parser->file);
	ft_putstr(":\n Error line ");
	ft_putnbr(parser->line);
	ft_putstr(": ");
	ft_putstr(s);
	exit(0);
}
