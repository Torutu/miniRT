#include "../miniRT.h"

t_vec calculate_pixel_center(t_cam *cam, int x, int y)
{
    t_vec px_center;
    px_center = vec_add(cam->fstpx, vec_mult(cam->px_size_x, x));
    px_center = vec_add(px_center, vec_mult(cam->px_size_y, y));
    return (px_center);
}

t_vec calculate_ray_direction(t_vec pixel_center, t_vec camera_point, t_vec camera_orient)
{
    t_vec ray_direction = norm_vec(vec_sub(pixel_center, camera_point));
    if (dot_vec(ray_direction, camera_orient) < 0)
        ray_direction = vec_mult(ray_direction, -1.0);
    return (ray_direction);
}

t_color	ray_color(t_ray ray, t_minirt rt)
{
	t_hit_info	h_rec;
	int				in_shadow;
	t_color			color;

	check_spheres(ray, rt, &h_rec);
	check_planes(ray, rt, &h_rec);
	check_cylinders(ray, rt, &h_rec);
	if (h_rec.t > 0.0)
	{
		rt.l.light_dir = norm_vec(vec_sub(rt.l.point, h_rec.point));
		if (rt.l.bright > rt.amb.ratio)
			check_shadow(rt, &in_shadow, h_rec);
		compute_lighting(&color, rt, h_rec);
		if (in_shadow == 1)
		{
			color = shadow_mult(color, (1.0 - ((rt.l.bright * 100.0)
							- (rt.amb.ratio * 100.0))));
		}
		return (color);
	}
	return ((t_color){0, 0, 0});
}

t_ray	init_ray(t_vec s, t_vec d)
{
	t_ray	r;

	r.start = s;
	r.direction = d;
	r.q = RAY_MAX;
	return (r);
}

t_vec	ray_point(t_ray r, float t)
{
	return (vec_add(r.start, vec_mult(r.direction, t)));
}
