/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectooor1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:48:44 by walnaimi          #+#    #+#             */
/*   Updated: 2025/01/07 12:32:53 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec	vec_div(t_vec a, float b)
{
	t_vec	c;

	if (b == 0)
	{
		printf("Can't divide with zero!\n");
		exit(1);
	}
	c.x = a.x / b;
	c.y = a.y / b;
	c.z = a.z / b;
	return (c);
}

float	dot_vec(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	cross_vec(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

t_vec	norm_vec(t_vec v)
{
	return (vec_div(v, vec_len(v)));
}
