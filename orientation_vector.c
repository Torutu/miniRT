/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_vector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:34:53 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/10 13:17:20 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	free_minirt_or(char **or)
{
	free_split(or);
	return (1);
}

static int	check_or(char *values)
{
	int	i;
	int	comma;
	
	i = 0;
	comma = 0;
	while (values[i] != '\0')
	{
		if (ft_isdigit(values[i]))
			i++;
		else if (values[i] == ' ' || values[i] == '.')
			i++;
		else if (values[i] == ',' && values[i + 1] != ',')
		{
			comma++;
			i++;
		}
		else if (values[i] == '-' && (i == 0 || values[i - 1] == ','))
			i++;
		else
			return (1);
	}
	if (comma != 2)
		return (1);
	return (0);
}

int	add_threed(char *values, t_arg *new)
{
	char	**or;
	int		i;

	i = 0;
	if (check_or(values) == 1)
		return (1);
	or = ft_split(values, ',');
	if (!or)
		return (1);
	if (or[0][0] == '.' || or[1][0] == '.' || or[2][0] == '.')
		return(free_minirt_or(or));
	new->coor3d.x = ft_atof(or[0]);
	new->coor3d.y = ft_atof(or[1]);
	new->coor3d.z = ft_atof(or[2]);
	if (new->coor3d.x > 1 || new->coor3d.x < -1 || new->coor3d.y > 1
		|| new->coor3d.y < -1 || new->coor3d.z > 1 || new->coor3d.z < -1)
		return (1);
	if ((ft_strlen(or[0]) > 3 || (new->coor3d.x < 0 && ft_strlen(or[0]) > 4)) 
		|| (ft_strlen(or[1]) > 3 || (new->coor3d.y < 0 && ft_strlen(or[1]) > 4))
		|| (ft_strlen(or[2]) > 3 || (new->coor3d.z < 0 && ft_strlen(or[2]) > 4)))
		return(free_minirt_or(or));
	free_split(or);
	return (0);
}
