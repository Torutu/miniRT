/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:13:40 by sataskin          #+#    #+#             */
/*   Updated: 2025/01/07 14:22:39 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	check_nodes_c(t_arg *list, t_minirt *rt, char **values)
{
	t_arg	*temp;

	temp = list;
	if (temp == NULL)
		return ;
	while (temp != NULL)
	{
		if (temp->c == 1)
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
	check_nodes_c(rt->l_list, rt, values);
	new = ft_calloc(1, sizeof(t_arg));
	if (!new)
	{
		free_split(values);
		free_minirt(rt, "Error: MALLOC FAIL\n");
	}
	new->next = NULL;
	new->c = 1;
	if (add_coor(values[1], new) == 1 || add_threed(values[2], new) == 1
		|| add_horizontal(values[3], new) == 1)
	{
		free_split(values);
		free(new);
		free_minirt(rt, "Error: Invalid Input\n");
	}
	ft_lstadd_back_rt(&rt->l_list, new);
}
