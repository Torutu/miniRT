/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:29:16 by sataskin          #+#    #+#             */
/*   Updated: 2025/01/09 14:08:24 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	free_minirt_coor(char **coor)
{
	free_split(coor);
	return (1);
}

static int	check_coor(char *values)
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

int	add_coor(char *values, t_arg *new)
{
	char	**coor;

	if (check_coor(values) == 1)
		return (1);
	coor = ft_split(values, ',');
	if (!coor)
		return (1);
	if (val_num(coor) == 1)
		return (free_minirt_coor(coor));
	new->coor.x = ft_atof(coor[0]);
	new->coor.y = ft_atof(coor[1]);
	new->coor.z = ft_atof(coor[2]);
	free_split(coor);
	return (0);
}
