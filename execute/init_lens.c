/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:47:02 by walnaimi          #+#    #+#             */
/*   Updated: 2025/01/07 12:08:26 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	calculate_viewport(t_minirt *rt, t_init_cam *i)
{
	rt->aspect_ratio = (float) WIDTH / HEIGHT;
	i->focal_length = (rt->width / 2) / (tanf((rt->cam.fov * (PI / 180)) / 2));
	i->vport_w = rt->width * 2;
	i->vport_h = i->vport_w / rt->aspect_ratio;
}

void	calculate_camera_axes(t_minirt *rt, t_init_cam *i)
{
	i->cam_forward = norm_vec(rt->cam.or_vec);
	if (vec_len(cross_vec((t_vec){0, 1, 0}, i->cam_forward)) != 0)
		i->cam_x_axis = norm_vec(cross_vec((t_vec){0, 1, 0}, i->cam_forward));
	else
		i->cam_x_axis = norm_vec(cross_vec((t_vec){0, 1, -0.00001},
					i->cam_forward));
	i->cam_y_axis = cross_vec(i->cam_forward, i->cam_x_axis);
}

void	calculate_scaled_viewport(t_minirt *rt, t_init_cam *i)
{
	i->vport_x = vec_mult(i->cam_x_axis, i->vport_w);
	i->vport_y = vec_mult(i->cam_y_axis, i->vport_h);
	rt->cam.px_size_x = vec_div(i->vport_x, rt->width);
	rt->cam.px_size_y = vec_div(i->vport_y, rt->height);
}

void	calculate_viewport_position(t_minirt *rt, t_init_cam *i)
{
	i->focal = vec_mult(i->cam_forward, i->focal_length);
	i->vport_up_l = vec_sub(rt->cam.point, i->focal);
	i->vport_up_l = vec_sub(i->vport_up_l, vec_div(i->vport_x, 2));
	i->vport_up_l = vec_sub(i->vport_up_l, vec_div(i->vport_y, 2));
}

void	calculate_pixel_origin(t_minirt *rt, t_init_cam *i)
{
	rt->cam.fstpx = vec_mult(vec_add(rt->cam.px_size_x,
				rt->cam.px_size_y), 0.5);
	rt->cam.fstpx = vec_add(rt->cam.fstpx, i->vport_up_l);
}
