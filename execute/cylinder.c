#include "../miniRT.h"

/**
 * Checks for intersections between a ray and a list of cylinders in the scene.
 * 
 * @param ray The ray to check for intersection.
 * @param rt The scene data, including the list of cylinders.
 * @param ray_info The hit record to store the intersection data.
 */
void	check_cylinders(t_ray ray, t_minirt rt, t_hit_info *ray_info)
{
	int		i;
	float	t;

	i = -1;
	while (++i < rt.cy_count)
	{
		t = hit_cylinder(rt.cy[i], ray);
		if ((i == 0 && (rt.sp_count == 0 && rt.pl_count == 0))
			|| (t > 0.0 && (ray_info->t < 0.0 || t < ray_info->t)))
		{
			ray_info->t = t;
			ray_info->point = ray_point(ray, t);
			ray_info->normal = cyl_normal(ray_info->point,
					rt.cy[i], rt.cy[i].height, rt.cy[i].radius);
			ray_info->color = color_mult(rt.cy[i].col, 255);
			ray_info->center = rt.cy[i].center;
			ray_info->id = i;
			ray_info->shape = 2;
		}
	}
}
