/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_field.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:37:02 by sataskin          #+#    #+#             */
/*   Updated: 2025/01/07 14:23:09 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* int FOV = 0 - 180 */

int	add_horizontal(char *values, t_arg *new)
{
	int	i;

	i = 0;
	while (values[i] != '\0')
	{
		if (ft_isdigit(values[i]) != 1)
			return (1);
		i++;
	}
	if (ft_strlen(values) > 3)
		return (1);
	new->fov = ft_atoi(values);
	if (new->fov > 180 || new->fov < 0)
		return (1);
	return (0);
}
