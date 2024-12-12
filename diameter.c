/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diameter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:26:02 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/12 13:43:33 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	add_diameter(char *str, t_arg *new)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '.')
			return (1);
		i++;
	}
	if (ft_strlen(str) > 4)
		return (1);
	new->diameter = ft_atoi(str);
	return (0);
}
