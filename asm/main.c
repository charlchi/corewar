/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:25:31 by cmoller           #+#    #+#             */
/*   Updated: 2018/11/24 16:25:41 by cmoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	int		a;
	int		i;

	a = 1;
	while (a < argc)
	{
		if ((i = ft_strlen(argv[a])) < 3)
			asm_err("Invalid file name");
		if (argv[a][i - 1] != 's' || argv[a][i - 2] != '.')
			asm_err("Invalid file extension, must end with \".s\"");
		parse_champion(argv[a]);
		a++;
	}
	return (0);
}
