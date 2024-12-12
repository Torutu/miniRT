/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:04:56 by sataskin          #+#    #+#             */
/*   Updated: 2024/11/21 13:19:15 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_nodes(t_arg *nodes, char i)
{
	t_arg *temp;

	temp = nodes;
	while (temp)
	{
		if (temp->A == 1 && i == 'A')
			return (1);
		if (temp->C == 1 && i == 'C')
			return (1);
		if (temp->L == 1 && i == 'L')
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	argument_count(char **values, int amount)
{
	int	i;

	i = 0;
	if (values == NULL)
		return (1);
	if (values[0] == NULL)
		return (1);
	while (values[i] != NULL)
		i++;
	if (i == amount && no_extras(values) == 0)
		return (0);
	else
		return (1);
}

int	count_commas(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!line)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int no_extras(char **array)
{
	int	i;
	int no;
	
	no = 1;
	while (array && array[no])
	{
		i = 0;
		while (array[no][i] != '\0' && array[no][i] != '\n')
		{
			if (array[no][i] < '0' || array[no][i] > '9')
			{
				if (array[no][i] != '.' && array[no][i] != ',')
					return (1);
			}
			i++;
		}
		no++;
	}
	return (0);
}

