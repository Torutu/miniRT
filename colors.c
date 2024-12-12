/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:53:45 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/10 11:08:55 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*	FORMAT
		∗ R,G,B colors in range [0-255]: 255, 255, 255
*/
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
		else if (values[i] == ' ')
			i++;
		else if (values[i] == ','  && values[i + 1] != ',')
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
	int		i;
	
	i = 0;
	if (check_colors(values) == 1)
		return (1);
	colors = ft_split(values, ',');
	if (!colors)
		return (1);
	while (colors[i] && i < 3)
	{
		if (ft_strlen(colors[i]) > 3)
			return(free_minirt_c(colors));
		i++;
	}
	new->color.R = ft_atoi(colors[0]);
	if (new->color.R > 255 || new->color.R < 0)
		return(free_minirt_c(colors));
	new->color.G = ft_atoi(colors[1]);
	if (new->color.G > 255 || new->color.G < 0)
		return(free_minirt_c(colors));
	new->color.B = ft_atoi(colors[2]);
	if (new->color.B > 255 || new->color.B < 0)
		return(free_minirt_c(colors));
	free_split(colors);
	return (0);
}
