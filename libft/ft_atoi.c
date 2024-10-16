/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:35:55 by sataskin          #+#    #+#             */
/*   Updated: 2023/11/15 12:15:11 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* a function that turns an array into it's an integer of it's numerical
representation. It first checks that the string exists and then skips all
the whitespace characters. Then it begins creating the string. */

#include "libft.h"

static int	ft_checkwhitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\f' || c == '\r' || c == '\v'
		|| c == '\n')
		return (1);
	else
		return (0);
}

int	ft_check_return(int sign)
{
	if (sign > 0)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long	number;
	int		index;
	int		sign;
	size_t	m;

	number = 0;
	index = 0;
	sign = 1;
	m = 0 - 1;
	while (ft_checkwhitespace(str[index]))
		index++;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while (str[index] <= '9' && str[index] >= '0')
	{
		if ((size_t)number > m / 10 - (str[index] - '0'))
			return (ft_check_return(sign));
		number = number * 10 + str[index] - '0';
		index++;
	}
	return ((int)number * sign);
}
