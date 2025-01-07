/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:12:06 by walnaimi          #+#    #+#             */
/*   Updated: 2025/01/07 13:14:53 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	apply_ambient(t_color obj_color, t_color amb_color, float ratio)
{
	t_color	result;

	if (amb_color.R == 255 && amb_color.G == 255 && amb_color.B == 255)
		return (obj_color);
	ratio *= 85;
	result.R = (1 - ratio) * obj_color.R + ratio * amb_color.R;
	result.G = (1 - ratio) * obj_color.G + ratio * amb_color.G;
	result.B = (1 - ratio) * obj_color.B + ratio * amb_color.B;
	if (result.R > 255)
		result.R = 255;
	if (result.G > 255)
		result.G = 255;
	if (result.B > 255)
		result.B = 255;
	return (result);
}

void	get_cylinder(t_minirt *rt, t_arg *temp, int i, int j)
{
	rt->cy[j].id = i;
	rt->cy[j].center.x = temp->coor.x;
	rt->cy[j].center.y = temp->coor.y;
	rt->cy[j].center.z = temp->coor.z;
	rt->cy[j].axis.x = temp->coor3d.x;
	rt->cy[j].axis.y = temp->coor3d.y;
	rt->cy[j].axis.z = temp->coor3d.z;
	rt->cy[j].radius = temp->diameter;
	rt->cy[j].height = temp->height;
	rt->cy[j].col.R = temp->color.R;
	rt->cy[j].col.G = temp->color.G;
	rt->cy[j].col.B = temp->color.B;
	rt->cy[j].col = apply_ambient(rt->cy[j].col, rt->amb.color, rt->amb.ratio);
}

void	get_plane(t_minirt *rt, t_arg *temp, int i, int j)
{
	rt->pl[j].id = i;
	rt->pl[j].point.x = temp->coor.x;
	rt->pl[j].point.y = temp->coor.y;
	rt->pl[j].point.z = temp->coor.z;
	rt->pl[j].normal.x = temp->coor3d.x;
	rt->pl[j].normal.y = temp->coor3d.y;
	rt->pl[j].normal.z = temp->coor3d.z;
	rt->pl[j].col.R = temp->color.R;
	rt->pl[j].col.G = temp->color.G;
	rt->pl[j].col.B = temp->color.B;
	rt->pl[j].col = apply_ambient(rt->pl[j].col, rt->amb.color, rt->amb.ratio);
}

void	get_sphere(t_minirt *rt, t_arg *temp, int i, int j)
{
	rt->sp[j].id = i;
	rt->sp[j].center.x = temp->coor.x;
	rt->sp[j].center.y = temp->coor.y;
	rt->sp[j].center.z = temp->coor.z;
	rt->sp[j].col.R = temp->color.R;
	rt->sp[j].col.G = temp->color.G;
	rt->sp[j].col.B = temp->color.B;
	rt->sp[j].radius = temp->diameter;
	rt->sp[j].col = apply_ambient(rt->sp[j].col, rt->amb.color, rt->amb.ratio);
}

void	get_light(t_minirt *rt, t_arg *temp, int i)
{
	rt->l.id = i;
	rt->l.point.x = temp->coor.x;
	rt->l.point.y = temp->coor.y;
	rt->l.point.z = temp->coor.z;
	rt->l.bright = temp->bright / 100;
}


