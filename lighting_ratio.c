/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_ratio.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:47:43 by sataskin          #+#    #+#             */
/*   Updated: 2025/01/09 14:43:51 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	val_post_dot(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i] != '\0' && str[i] != '.')
		i++;
	if (str[i] == '\0')
		return (0);
	i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
		num++;
	}
	if (num > 4 || num == 0)
		return (1);
	return (0);
}

static int	val_pre_dot(char *str)
{
	int	i;
	int	min;

	i = 0;
	min = 0;
	if (str[i] == '-')
		min++;
	i += min;
	while (str[i] != '\0')
	{
		if (str[i] == '.')
			break ;
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	if ((i - min) > 4 || (i - min) == 0)
		return (1);
	return (0);
}

static int	validate_string(char *str)
{
	if (val_pre_dot(str) == 1)
		return (1);
	if (val_post_dot(str) == 1)
		return (1);
	return (0);
}

int	add_lighting_ratio(char *str, t_arg *new)
{
	if (validate_string(str) == 1)
		return (1);
	new->l_rat = ft_atof(str);
	if (new->l_rat > 1.0 || new->l_rat < 0)
		return (1);
	return (0);
}
