/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_labels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgerber <mgerber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 09:13:40 by mgerber           #+#    #+#             */
/*   Updated: 2018/09/24 12:39:13 by mgerber          ###   ########.fr       */
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
	return (str[i - 1] == ':' ? 1 : 0);
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
	if (is_label(instructions[j]))
		add_label(instructions[j++], i, list);
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

void		first_pass(t_parser *parser, t_labels **list)
{
	int		i;
	char	*asml;

	i = 0;
	while ((asml = get_asm_line(parser)))
		i = create_labels(parser, asml, i, list);
}

