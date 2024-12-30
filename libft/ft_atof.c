/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:19:52 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/23 16:03:43 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float  ft_atof(const char *str)
{
        float  res;
        float  res2;
        char    *c;
        int             len;
        int             sign;

        sign = 1;
        c = (char *)str;
        if (str[0] == '-')
        {
                sign *= -1;
                c++;
        }
        res = (float)ft_atoi(c);
        while (*c && *c != '.')
                c++;
        if (*c == '.')
                c++;
        res2 = (float)ft_atoi(c);
        len = ft_strlen(c);
        while (len--)
                res2 /= 10;
        return (sign * (res + res2));
}
