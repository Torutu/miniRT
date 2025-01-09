/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:47:08 by walnaimi          #+#    #+#             */
/*   Updated: 2025/01/09 14:08:24 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float	hit_plane(t_vec norm, t_vec point, t_ray ray)
{
	float	denom;
	float	p;

	denom = dot_vec(norm, ray.direction);
	if (fabs(denom) > 0.00001f)
	{
		p = dot_vec(vec_sub(point, ray.start), norm) / denom;
		return (p);
	}
	return (-1.0);
}

void	check_planes(t_ray ray, t_minirt rt, t_hit_info *ray_info)
{
	int		i;
	float	t;

	i = -1;
	while (++i < rt.pl_count)
	{
		t = hit_plane(rt.pl[i].normal, rt.pl[i].point, ray);
		if ((i == 0 && rt.pl_count == 0)
			|| (t > 0.0 && (ray_info->t < 0.0 || t < ray_info->t)))
		{
			ray_info->t = t;
			ray_info->point = ray_point(ray, t);
			ray_info->normal = rt.pl[i].normal;
			ray_info->color = color_mult(rt.pl[i].col, 255);
			ray_info->center = rt.pl[i].point;
			ray_info->id = i;
			ray_info->shape = 1;
		}
	}
}
