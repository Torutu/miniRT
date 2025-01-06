#include "../miniRT.h"

float	hit_top_cap(t_vec axis_dir, t_vec top_cap_c, t_ray ray, float r)
{
	float		cy_top;
	t_vec		point_top;
	t_vec		vec_top;

	cy_top = hit_plane(axis_dir, top_cap_c, ray);
	if (cy_top > 0.0f)
	{
		point_top = vec_add(ray.start, vec_mult(ray.direction, cy_top));
		vec_top = vec_sub(point_top, top_cap_c);
		if (dot_vec(vec_top, vec_top) > r * r)
			cy_top = -1.0f;
	}
	return (cy_top);
}

float	hit_bot_cap(t_vec axis_dir, t_vec bot_cap_c, t_ray ray, float r)
{
	float		t_cap_bot;
	t_vec		point_bot;
	t_vec		vec_bot;

	t_cap_bot = hit_plane(axis_dir, bot_cap_c, ray);
	if (t_cap_bot > 0.0f)
	{
		point_bot = vec_add(ray.start, vec_mult(ray.direction, t_cap_bot));
		vec_bot = vec_sub(point_bot, bot_cap_c);
		if (dot_vec(vec_bot, vec_bot) > r * r)
			t_cap_bot = -1.0f;
	}
	return (t_cap_bot);
}

float	hit_cyl_body(t_ray ray, t_cy c, float r, float h)
{
	t_cyl_body	cy;

	cy.oc = vec_sub(ray.start, c.center);
	cy.oc_perp = vec_sub(cy.oc, vec_mult(c.axis, dot_vec(cy.oc, c.axis)));
	cy.ray_dir_perp = vec_sub(ray.direction,
			vec_mult(c.axis, dot_vec(ray.direction, c.axis)));
	cy.a = dot_vec(cy.ray_dir_perp, cy.ray_dir_perp);
	cy.b = 2.0f * dot_vec(cy.ray_dir_perp, cy.oc_perp);
	cy.c = dot_vec(cy.oc_perp, cy.oc_perp) - r * r;
	cy.discriminant = cy.b * cy.b - 4.0f * cy.a * cy.c;
	if (cy.discriminant < 0.0f)
		return (-1.0f);
	cy.sqrt_discriminant = sqrtf(cy.discriminant);
	cy.t1 = (-cy.b - cy.sqrt_discriminant) / (2.0f * cy.a);
	cy.t2 = (-cy.b + cy.sqrt_discriminant) / (2.0f * cy.a);
	cy.t_cylinder = -1.0f;
	cy.p1 = vec_add(ray.start, vec_mult(ray.direction, cy.t1));
	cy.p2 = vec_add(ray.start, vec_mult(ray.direction, cy.t2));
	cy.z1 = dot_vec(vec_sub(cy.p1, c.center), c.axis);
	cy.z2 = dot_vec(vec_sub(cy.p2, c.center), c.axis);
	if (cy.t1 > 0 && cy.z1 >= -h / 2.0f && cy.z1 <= h / 2.0f)
		cy.t_cylinder = cy.t1;
	else if (cy.t2 > 0 && cy.z2 >= -h / 2.0f && cy.z2 <= h / 2.0f)
		cy.t_cylinder = cy.t2;
	return (cy.t_cylinder);
}

float	hit_cylinder(t_cy c, t_ray ray)
{
	float		t_cylinder;
	float		cy_top;
	float		cy_bottom;
	t_vec		top_cap_center;
	t_vec		bot_cap_center;

	c.axis = norm_vec(c.axis);
	bot_cap_center = vec_sub(c.center, vec_mult(c.axis, c.height / 2.0f));
	top_cap_center = vec_add(c.center, vec_mult(c.axis, c.height / 2.0f));
	t_cylinder = hit_cyl_body(ray, c, c.radius, c.height);
	cy_top = hit_top_cap(c.axis, top_cap_center, ray, c.radius);
	cy_bottom = hit_bot_cap(c.axis, bot_cap_center, ray, c.radius);
	if (t_cylinder < 0.0f || (cy_top > 0.0f && cy_top < t_cylinder))
		t_cylinder = cy_top;
	if (t_cylinder < 0.0f || (cy_bottom > 0.0f && cy_bottom < t_cylinder))
		t_cylinder = cy_bottom;
	return (t_cylinder);
}

t_vec	cyl_normal(t_vec point, t_cy c, float height, float radius)
{
	t_vec	bottom_center;
	t_vec	top_center;
	t_vec	surface_normal;
	float	t;
	t_vec	pt;

	c.axis = norm_vec(c.axis);
	bottom_center = vec_sub(c.center, vec_mult(c.axis, height / 2.0f));
	top_center = vec_add(c.center, vec_mult(c.axis, height / 2.0f));
	if (vec_len(vec_sub(point, top_center)) < radius)
		return (c.axis);
	if (vec_len(vec_sub(point, bottom_center)) < radius)
		return (vec_mult(c.axis, -1.0f));
	t = dot_vec(vec_sub(point, bottom_center), c.axis);
	pt = vec_add(bottom_center, vec_mult(c.axis, t));
	surface_normal = norm_vec(vec_sub(point, pt));
	return (surface_normal);
}