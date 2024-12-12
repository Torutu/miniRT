/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:41:41 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/12 13:46:38 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	add_height(char *str, t_arg *new)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && str[i] == '-')
			i++;
		if (ft_isdigit(str[i]) || str[i] == '.')
			i++;
		else
			return (1);
	}
	if (ft_strlen(str) > 6)
		return (1);
	new->height = ft_atof(str);
	return (0);
}

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

void	add_cylinder(char **values, t_minirt *rt)
{
	t_arg	*new;

	if (arguments(values, 6) > 0)
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
	new->cy = 1;
	if (add_threed(values[2], new) == 1 || add_diameter(values[3], new) == 1
	|| add_coor(values[1], new) == 1 || add_height(values[4], new) == 1
	|| add_threed(values[2], new) == 1)
	{
		free_split(values);
		free_minirt(rt, "Error: Invalid Input\n");		
	}
	ft_lstadd_back_rt(&rt->l_list, new);
}

//add_threed(values[2], new) == 1 ||