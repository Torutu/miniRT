/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:53:45 by sataskin          #+#    #+#             */
/*   Updated: 2025/01/07 13:05:49 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	free_minirt_c(char **colors)
{
	free_split(colors);
	return (1);
}

static int	check_colors(char *values)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (values[i] != '\0')
	{
		if (ft_isdigit(values[i]))
			i++;
		else if (values[i] == ',' && values[i + 1] != ','
			&& values[i + 1] != '\0')
		{
			comma++;
			i++;
		}
		else
			return (1);
	}
	if (comma != 2)
		return (1);
	return (0);
}

int	add_colors(char *values, t_arg *new)
{
	char	**colors;

	if (check_colors(values) == 1)
		return (1);
	colors = ft_split(values, ',');
	if (!colors)
		return (1);
	if (val_num(colors) == 1)
		return (free_minirt_c(colors));
	new->color.R = ft_atoi(colors[0]);
	if (new->color.R > 255 || new->color.R < 0)
		return (free_minirt_c(colors));
	new->color.B = ft_atoi(colors[1]);
	if (new->color.B > 255 || new->color.B < 0)
		return (free_minirt_c(colors));
	new->color.G = ft_atoi(colors[2]);
	if (new->color.G > 255 || new->color.G < 0)
		return (free_minirt_c(colors));
	free_split(colors);
	return (0);
}
