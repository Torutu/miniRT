#include "../miniRT.h"

static int	sphere_shadow(t_minirt rt, int *in_shadow, t_hit_info h_rec)
{
	int	i;

	i = -1;
	while (++i < rt.sp_count)
	{
		if (hit_sphere(rt.sp[i].center, rt.sp[i].radius, rt.l.shadow_ray) > 0.0)
		{
			if (h_rec.shape == 0 && h_rec.id == i)
				continue ;
			*in_shadow = 1;
			return (1);
		}
	}
	return (0);
}

static int	cylinder_shadow(t_minirt rt, int *in_shadow, t_hit_info h_rec)
{
	int	i;

	i = -1;
	while (++i < rt.cy_count)
	{
		if (hit_cylinder(rt.cy[i], rt.l.shadow_ray) > 0.0)
		{
			if (h_rec.shape == 2 && h_rec.id == i)
				continue ;
			*in_shadow = 1;
			return (1);
		}
	}
	return (0);
}

static void	plane_shadow(t_minirt rt, int *in_shadow, t_hit_info h_rec)
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
				if (h_rec.shape == 1 && h_rec.id == i)
					continue ;
				*in_shadow = 1;
				return ;
			}
		}
	}
}

void	compute_lighting(t_color *color, t_minirt rt, t_hit_info h_rec)
{
	float		diffuse_strength;
	t_vec		diffuse;

	rt.l.light_color = (t_vec){1.0, 1.0, 1.0};
	rt.l.lighting = (t_vec){1.0, 1.0, 1.0};
	diffuse_strength = fmaxf(0.0, dot_vec(rt.l.light_dir, h_rec.normal));
	diffuse = vec_mult(rt.l.light_color, diffuse_strength);
	rt.l.lighting = vec_add(vec_mult((t_vec)
			{rt.amb.ratio, rt.amb.ratio, rt.amb.ratio}, 0.3),
			vec_mult(diffuse, rt.l.bright));
	*color = (t_color){h_rec.color.R * rt.l.lighting.x,
		h_rec.color.G * rt.l.lighting.y, h_rec.color.B * rt.l.lighting.z};
	color->R = fminf(fmaxf(color->R, 0.0), 255.0);
	color->G = fminf(fmaxf(color->G, 0.0), 255.0);
	color->B = fminf(fmaxf(color->B, 0.0), 255.0);
}

void	check_shadow(t_minirt rt, int *in_shadow, t_hit_info h_rec)
{
	rt.l.shadow_ray.start = h_rec.point;
	rt.l.shadow_ray.direction = rt.l.light_dir;
	*in_shadow = 0;
	if (sphere_shadow(rt, in_shadow, h_rec) == 1)
		return ;
	if (cylinder_shadow(rt, in_shadow, h_rec) == 1)
		return ;
	plane_shadow(rt, in_shadow, h_rec);
}