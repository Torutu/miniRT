#include "../miniRT.h"

// float	hit_sphere(t_vec center, float radius, t_ray ray)
// {
// 	t_vec	og_to_cent;
// 	float	a;
// 	float	b;
// 	float	c;
// 	float	discriminant;

// 	og_to_cent = vec_sub(center, ray.start);
// 	a = dot_vec(ray.direction, ray.direction);
// 	b = -2.0 * dot_vec(ray.direction, og_to_cent);
// 	c = dot_vec(og_to_cent, og_to_cent) - radius * radius;
// 	discriminant = b * b - 4 * a * c;
// 	if (discriminant < 0)
// 		return (-1.0);
// 	return ((-b - sqrtf(discriminant)) / (2.0 * a));
// }

float	hit_sphere(t_vec center, float radius, t_ray ray)
{
	t_vec	og_to_cent;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t1;
	float	t2;
	// Calculate the quadratic coefficients
	og_to_cent = vec_sub(center, ray.start);
	a = dot_vec(ray.direction, ray.direction);
	b = -2.0 * dot_vec(ray.direction, og_to_cent);
	c = dot_vec(og_to_cent, og_to_cent) - radius * radius;
	// Calculate the discriminant
	discriminant = b * b - 4 * a * c;
	// If the discriminant is negative, there are no intersections
	if (discriminant < 0)
		return (-1.0);
	// Calculate the two intersection points
	t1 = (-b - sqrtf(discriminant)) / (2.0 * a); // Closer intersection
	t2 = (-b + sqrtf(discriminant)) / (2.0 * a); // Farther intersection
	if (t1 > RAY_MIN)// Return the smallest positive t value (valid intersection)
		return (t1);
	if (t2 > RAY_MIN)
		return (t2);
	return (-1.0);// If both t1 and t2 are negative, no valid intersection
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

