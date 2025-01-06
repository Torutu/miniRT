#include "../miniRT.h"

/**
 * Checks for intersections between a ray and a list of cylinders in the scene.
 * 
 * @param ray The ray to check for intersection.
 * @param rt The scene data, including the list of cylinders.
 * @param h_rec The hit record to store the intersection data.
 */
void	check_cylinders(t_ray ray, t_minirt rt, t_hit_info *h_rec)
{
	int		i;
	float	t;

	i = -1;
	while (++i < rt.cy_count)
	{
		t = hit_cylinder(rt.cy[i], ray);
		if ((i == 0 && (rt.sp_count == 0 && rt.pl_count == 0))
			|| (t > 0.0 && (h_rec->t < 0.0 || t < h_rec->t)))
		{
			h_rec->t = t;
			h_rec->point = ray_point(ray, t);
			h_rec->normal = cyl_normal(h_rec->point,
					rt.cy[i], rt.cy[i].height, rt.cy[i].radius);
			h_rec->color = color_mult(rt.cy[i].col, 255);
			h_rec->center = rt.cy[i].center;
			h_rec->id = i;
			h_rec->shape = 2;
		}
	}
}
