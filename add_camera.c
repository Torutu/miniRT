/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:13:40 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/10 13:08:39 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Input form
C -50,0,20 0,0,0 70

WHAT DO I WANT FOR THIS TO DO?
1. Check if there already is an A
2. split the arguments again for colors and for range
3. Check if the values are okay
*/
#include "miniRT.h"

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
static void	check_nodes_C(t_arg *list, t_minirt *rt, char **values)
{
	t_arg *temp;

	temp = list;
	if (temp == NULL)
		return;
	while (temp != NULL)
	{
		if (temp->C == 1)
		{
			free_split(values);
			free_minirt(rt, "ERROR: MULTIPLE CAMERA\n");
		}
		temp = temp->next;
	}
}

void	add_camera(char **values, t_minirt *rt)
{
	t_arg	*new;
	
	if (arguments(values, 4) > 0)
	{
		free_split(values);
		free_minirt(rt, "ERROR: Invalid Camera\n");
	}
	check_nodes_C(rt->l_list, rt, values);
	new = ft_calloc(1, sizeof(t_arg));
	if (!new)
	{
		free_split(values);
		free_minirt(rt, "Error: MALLOC FAIL\n");
	}
	new->next = NULL;
	new->C = 1;
	if (add_coor(values[1], new) == 1 || add_threed(values[2], new) == 1
		|| add_horizontal(values[3], new) == 1)
	{
		free_split(values);
		free_minirt(rt, "Error: Invalid Input\n");
	}
	ft_lstadd_back_rt(&rt->l_list, new);
}
/*
	int C = Camera (need below);
	int x = coordinate; 
	int y = coordinate;
	int z = coordinate;
	int Xnv = 3d normalized orientation vector [-1,1];
	int Ynv = 3d normalized orientation vector [-1,1];
	int Znv = 3d normalized orientation vector [-1,1];
	int FOV = Horizontal field of view [0,180];*/