/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_height.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:53:10 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/27 11:54:08 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int  val_post_dot(char *str)
{
    int i;
    int num;
    
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
    if (num > 3 || num == 0)
        return (1);
    return (0);
}

static int  val_pre_dot(char *str)
{
    int i;
    int min;
    
    i = 0;
    min = 0;
    if (str[i] == '-')
        min++;
    i += min;
    while (str[i] != '\0')
    {
        if (str[i] == '.')
            break;
        if (ft_isdigit(str[i]) == 0)
            return (1);
        i++;
    }
    if ((i - min) > 3 || (i - min) == 0)
        return (1);
    return (0);
}

static int  val_string(char *str)
{
    if (val_pre_dot(str) == 1)
        return (1);
    if (val_post_dot(str) == 1)
        return (1);
    return (0);
}

int	add_height(char *str, t_arg *new)
{
	if (val_string(str) == 1)
        return (1);
	new->height = ft_atof(str);
	return (0);
}