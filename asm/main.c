/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 09:13:40 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/12 12:33:53 by mgerber          ###   ########.fr       */
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