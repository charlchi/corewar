/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 09:13:40 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/25 12:29:56 by mgerber          ###   ########.fr       */
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

t_labels	*new_label(char *str, int i)
{
	t_labels	*label;

	label = (t_labels*)malloc(sizeof(t_labels));
	label->name = ft_strdup(str);
	ft_strchr(label->name, ':')[0] = '\0';
	label->index = i;
	label->next = NULL;
	return (label);
}

void		add_label(char *str, int i, t_labels **list)
{
	t_labels	*label;
	t_labels	*head;

	label = new_label(str, i);
	head = *list;
	if (head) // this is not supposed to be true if there have been no labels thus far, however I have not been able to get it to do as such
	{
		while (head->next)
			head = head->next;
		head->next = label;
	}
	else
		*list = label;
}



int			instruction_val(t_parser *parser, char *str, int k)
{
	if (str[0] == 'r')
		return (1);
	if (str[0] == '%')
		return (parser->op_tab[k].label_size ? DIR_SIZE / 2 : DIR_SIZE);
	return (IND_SIZE);
}

int			create_labels(t_parser *parser, char *asml, int i, t_labels **list)
{
	char	*r;
	char	**instructions;
	int		j;
	int		k;

	j = 0;
	k = -1;
	while ((r = ft_strchr(asml, SEPARATOR_CHAR)))
		*r = ' ';
	instructions = ft_strsplit(asml, ' ');
	if (instructions && is_label(instructions[j]))
		add_label(instructions[j++], i, list);
	if (instructions && instructions[1])
	{
		while (++k < 17)
		{
			if (ft_strequ(instructions[j], parser->op_tab[k].name))
			{
				
				i += (parser->op_tab[k].acb ? 2 : 1);
				break ;
			}
		}
		while (instructions[++j])
			i += instruction_val(parser, instructions[j], k);
	}
	free_split(instructions);
	return (i);
}

int			get_label_index(t_labels *list, char *label)
{
	t_labels	*curr;

	curr = list;
	while (curr)
	{
		if (ft_strequ(curr->name, label))
			return (curr->index);
		curr = curr->next;
	}
	return (-1);

}

int			first_pass(t_parser *parser, t_labels **list)
{
	int		i;
	char	*asml;

	i = 0;
	while ((asml = get_asm_line(parser)))
	{
		i = create_labels(parser, asml, i, list);
		free(asml);
	}
	return (i);
}

/*


0000000 00 ea 83 f3 74 75 72 74 6c 65 00 00 00 00 00 00
0000010 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
*
0000080 00 00 00 00 00 00 00 00 00 00 01 8a 54 55 52 54
0000090 4c 45 20 46 46 53 20 55 20 4c 41 4d 41 00 00 00
00000a0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
*
0000890 0b 68 01 00 df 00 01 0b 68 01 00 35 00 01 0b 68
00008a0 01 00 d9 00 01 0b 68 01 00 11 00 01 02 90 00 00
00008b0 00 00 10 0c 00 bc 01 00 00 00 2a 02 90 1a 2b 00
00008c0 f0 02 02 90 00 00 00 00 10 0c 00 ae 01 00 00 00
00008d0 2a 03 70 02 fe 70 03 70 02 fe 70 03 70 02 fe 70
00008e0 03 70 02 fe 70 03 70 02 fe 70 03 70 02 fe 70 03
00008f0 70 02 fe 70 03 70 02 fe 70 03 70 02 fe 70 03 70
0000900 02 fe 70 03 70 02 fe 70 03 70 02 fe 70 03 70 02
0000910 fe 70 03 70 02 fe 70 03 70 02 fe 70 03 70 02 fe
0000920 70 03 70 02 fe 70 03 70 02 fe 70 03 70 02 fe 70
0000930 03 70 02 fe 70 03 70 02 fe 70 03 70 02 fe 70 03
0000940 70 02 fe 70 03 70 02 fe 70 03 70 02 fe 70 03 70
0000950 02 fe 70 03 70 02 fe 70 03 70 02 fe 70 03 70 02
0000960 fe 70 03 70 02 fe 70 03 70 02 fe 70 09 ff 60 01
0000970 00 00 00 2a 09 ff fb 01 00 00 00 2a 03 70 02 01
0000980 90 03 70 02 01 90 03 70 02 01 90 03 70 02 01 90
0000990 03 70 02 01 90 03 70 02 01 90 03 70 02 01 90 03
00009a0 70 02 01 90 03 70 02 01 90 03 70 02 01 90 03 70
00009b0 02 01 90 03 70 02 01 90 03 70 02 01 90 03 70 02
00009c0 01 90 03 70 02 01 90 03 70 02 01 90 03 70 02 01
00009d0 90 03 70 02 01 90 03 70 02 01 90 03 70 02 01 90
00009e0 03 70 02 01 90 03 70 02 01 90 03 70 02 01 90 03
00009f0 70 02 01 90 03 70 02 01 90 03 70 02 01 90 03 70
0000a00 02 01 90 03 70 02 01 90 03 70 02 01 90 03 70 02
0000a10 01 90 03 70 02 01 90 09 ff 60
*/