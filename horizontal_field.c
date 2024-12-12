/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_field.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:37:02 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/10 12:50:38 by sataskin         ###   ########.fr       */
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
	new->FOV = ft_atoi(values);
	if (new->FOV > 180 || new->FOV < 0)
		return (1);
	return (0);
}
