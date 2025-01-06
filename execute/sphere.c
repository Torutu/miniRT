#include "../miniRT.h"

float	hit_sphere(t_vec center, float radius, t_ray ray)
{
	t_sp_body	sp;
	sp.og_to_cent = vec_sub(center, ray.start);
	sp.a = dot_vec(ray.direction, ray.direction);
	sp.b = -2.0 * dot_vec(ray.direction, sp.og_to_cent);
	sp.c = dot_vec(sp.og_to_cent, sp.og_to_cent) - radius * radius;
	sp.discriminant = sp.b * sp.b - 4 * sp.a * sp.c;
	if (sp.discriminant < 0)
		return (-1.0);
	sp.t1 = (-sp.b - sqrtf(sp.discriminant)) / (2.0 * sp.a);
	sp.t2 = (-sp.b + sqrtf(sp.discriminant)) / (2.0 * sp.a);
	if (sp.t1 > RAY_MIN)
		return (sp.t1);
	if (sp.t2 > RAY_MIN)
		return (sp.t2);
	return (-1.0);
}


void	check_spheres(t_ray ray, t_minirt rt, t_hit_info *ray_info)
{
	int		i;
	float	t;

	ray_info->t = -1;
	i = -1;
	while (++i < rt.sp_count)
	{
		t = hit_sphere(rt.sp[i].center, rt.sp[i].radius, ray);
		if (i == 0 || (t > 0.0 && (ray_info->t < 0.0 || t < ray_info->t)))
		{
			ray_info->t = t;
			ray_info->point = ray_point(ray, t);
			ray_info->normal = norm_vec(vec_sub(ray_info->point, rt.sp[i].center));
			ray_info->color = color_mult(rt.sp[i].col, 255);
			ray_info->center = rt.sp[i].center;
			ray_info->id = i;
			ray_info->shape = 0;
		}
	}
}

