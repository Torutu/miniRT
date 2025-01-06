#include "../miniRT.h"

static void init_lens(t_minirt *rt)
{
	t_init_cam i;

	calculate_viewport(rt, &i);
	calculate_camera_axes(rt, &i);
	calculate_scaled_viewport(rt, &i);
	calculate_viewport_position(rt, &i);
	calculate_pixel_origin(rt, &i);
}

static void render_scene(t_minirt *rt)
{
	t_render r;

	r.y = -1;
	while (++r.y < rt->height)
	{
		r.x = -1;
		while (++r.x < rt->width)
		{
			r.px_center = calculate_pixel_center(&rt->cam, r.x, r.y);
			r.ray_direction = calculate_ray_direction(r.px_center, rt->cam.point, rt->cam.or_vec);
			r.ray = init_ray(rt->cam.point, r.ray_direction);
			r.color = ray_color(r.ray, *rt);
			r.rgba = get_rgba(r.color.R, r.color.G, r.color.B, 255);
			set_px_col(rt->img, r.x, r.y, r.rgba);
		}
	}
}

void    execution(t_minirt *rt)
{
	init_lens(rt);
	render_scene(rt);
}
