/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_legend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:48:32 by walnaimi          #+#    #+#             */
/*   Updated: 2025/01/07 14:21:20 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static int	sphere_shadow(t_minirt rt, int *in_shadow, t_hit_info ray_info)
{
	int	i;

	i = -1;
	while (++i < rt.sp_count)
	{
		if (hit_sphere(rt.sp[i].center, rt.sp[i].radius, rt.l.shadow_ray) > 0.0)
		{
			if (ray_info.shape == 0 && ray_info.id == i)
				continue ;
			*in_shadow = 1;
			return (1);
		}
	}
	return (0);
}

static int	cylinder_shadow(t_minirt rt, int *in_shadow, t_hit_info ray_info)
{
	int	i;

	i = -1;
	while (++i < rt.cy_count)
	{
		if (hit_cylinder(rt.cy[i], rt.l.shadow_ray) > 0.0)
		{
			if (ray_info.shape == 2 && ray_info.id == i)
				continue ;
			*in_shadow = 1;
			return (1);
		}
	}
	return (0);
}

static void	plane_shadow(t_minirt rt, int *in_shadow, t_hit_info ray_info)
{
	int		i;
	float	t_hit;
	float	light_dist;

	i = -1;
	while (++i < rt.pl_count)
	{
		t_hit = hit_plane(rt.pl[i].normal, rt.pl[i].point, rt.l.shadow_ray);
		if (t_hit > 0.0)
		{
			light_dist = vec_len(rt.l.light_dir);
			if (t_hit < light_dist)
			{
				if (ray_info.shape == 1 && ray_info.id == i)
					continue ;
				*in_shadow = 1;
				return ;
			}
		}
	}
}

void	compute_lighting(t_color *color, t_minirt rt, t_hit_info ray_info)
{
	float		diffuse_strength;
	t_vec		diffuse;

	rt.l.light_color = (t_vec){1.0, 1.0, 1.0};
	rt.l.lighting = (t_vec){1.0, 1.0, 1.0};
	diffuse_strength = fmaxf(0.0, dot_vec(rt.l.light_dir, ray_info.normal));
	diffuse = vec_mult(rt.l.light_color, diffuse_strength);
	rt.l.lighting = vec_add(vec_mult((t_vec)
			{rt.amb.ratio, rt.amb.ratio, rt.amb.ratio}, 0.3),
			vec_mult(diffuse, rt.l.bright));
	*color = (t_color){ray_info.color.red * rt.l.lighting.x,
		ray_info.color.green * rt.l.lighting.y, ray_info.color.blue * rt.l.lighting.z};
	color->red = fminf(fmaxf(color->red, 0.0), 255.0);
	color->green = fminf(fmaxf(color->green, 0.0), 255.0);
	color->blue = fminf(fmaxf(color->blue, 0.0), 255.0);
}

void	check_shadow(t_minirt rt, int *in_shadow, t_hit_info ray_info)
{
	rt.l.shadow_ray.start = ray_info.point;
	rt.l.shadow_ray.direction = rt.l.light_dir;
	*in_shadow = 0;
	if (sphere_shadow(rt, in_shadow, ray_info) == 1)
		return ;
	if (cylinder_shadow(rt, in_shadow, ray_info) == 1)
		return ;
	plane_shadow(rt, in_shadow, ray_info);
}
