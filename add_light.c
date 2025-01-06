/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:19:43 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/27 12:32:47 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
	int L = Light (need xyz and below);
	int bright = light brightness ratio [0.0,1.0];
*/

static int	arguments(char **values, int amount)
{
	int	i;

	i = 0;
	if (values == NULL)
		return (1);
	if (values[0] == NULL)
		return (1);
	while (values[i] != NULL)
		i++;
	if (i == amount)
		return (0);
	else
		return (1);
}

static int	add_brightness(char *str, t_arg *new)
{
	if (ft_strlen(str) > 3)
		return (1);
	new->bright = ft_atof(str);
	if (new->bright > 1.0 || new->bright < 0)
		return (1);
	return (0);
}

static void	check_nodes_L(t_arg *list, t_minirt *rt, char **values)
{
	t_arg *temp;

	temp = list;
	if (temp == NULL)
		return;
	while (temp != NULL)
	{
		if (temp->L == 1)
		{
			free_split(values);
			free_minirt(rt, "ERROR: MULTIPLE CAMERA\n");
		}
		temp = temp->next;
	}
}

void add_light(char **values, t_minirt *rt)
{
	t_arg	*new;

	if (arguments(values, 4) > 0)
	{
		free_split(values);
		free_minirt(rt, "Error: Invalid Light");
	}
	check_nodes_L(rt->l_list, rt, values);
	new = ft_calloc(1, sizeof(t_arg));
	if (!new)
	{
		free_split(values);
		free_minirt(rt, "ERROR: MALLOC FAIL\n");
	}
	new->next = NULL;
	new->L = 1;
	if (add_coor(values[1], new) == 1 || add_brightness(values[2], new) == 1)
	{
		free_split(values);
		free(new);
		free_minirt(rt, "Error: Invalid Input\n");
	}
	ft_lstadd_back_rt(&rt->l_list, new);
}
