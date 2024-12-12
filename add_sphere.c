/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:15:02 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/10 16:36:16 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*int sp = Sphere (need xyz, RGB and below);
	int diameter = sphere diameter;*/

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

void	add_sphere(char **values, t_minirt *rt)
{
	t_arg	*new;

	if (arguments(values, 4) > 0)
	{
		free_split(values);
		free_minirt(rt, "ERROR: Invalid Sphere\n");		
	}
	new = ft_calloc(1, sizeof(t_arg));
	if (!new)
	{
		free_split(values);
		free_minirt(rt, "Error: MALLOC FAIL\n");
	}
	new->next = NULL;
	new->sp = 1;
	if (add_coor(values[1], new) == 1 || add_colors(values[3], new) == 1
		|| add_diameter(values[2], new) == 1)
	{
		free_split(values);
		free_minirt(rt, "Error: Invalid Input\n");		
	}
	ft_lstadd_back_rt(&rt->l_list, new);
}
