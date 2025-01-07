/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ambient.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:07:54 by sataskin          #+#    #+#             */
/*   Updated: 2025/01/07 12:40:19 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Input form
A 0.2 255,255,255 

WHAT DO I WANT FOR THIS TO DO?
1. Check if there already is an A
2. split the arguments again for colors and for range
3. Check if the values are okay
*/

static void	check_nodes_a(t_arg *list, t_minirt *rt, char **values)
{
	t_arg	*temp;

	temp = list;
	if (temp == NULL)
		return ;
	while (temp != NULL)
	{
		if (temp->A == 1)
		{
			free_split(values);
			free_minirt(rt, "ERROR: MULTIPLE AMBIENT LIGHT\n");
		}
		temp = temp->next;
	}
}

void	add_ambient(char **values, t_minirt *rt)
{
	t_arg	*new;

	if (argument_count(values, 3) > 0)
	{
		free_split(values);
		free_minirt(rt, "ERROR: Invalid Ambient Lighting\n");
	}
	check_nodes_a(rt->l_list, rt, values);
	new = ft_calloc(1, sizeof(t_arg));
	if (!new)
	{
		free_split(values);
		free_minirt(rt, "Error: MALLOC FAIL\n");
	}
	new->next = NULL;
	new->A = 1;
	if (add_lighting_ratio(values[1], new) == 1
		|| add_colors(values[2], new) == 1)
	{
		free_split(values);
		free(new);
		free_minirt(rt, "Error: Invalid Input\n");
	}
	ft_lstadd_back_rt(&rt->l_list, new);
}
