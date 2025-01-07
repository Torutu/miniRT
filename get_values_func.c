/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:12:06 by walnaimi          #+#    #+#             */
/*   Updated: 2025/01/07 14:15:56 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	apply_ambient(t_color obj_color, t_color amb_color, float ratio)
{
	t_color	result;

	if (amb_color.red == 255 && amb_color.green == 255 && amb_color.blue == 255)
		return (obj_color);
	ratio *= 85;
	result.red = (1 - ratio) * obj_color.red + ratio * amb_color.red;
	result.green = (1 - ratio) * obj_color.green + ratio * amb_color.green;
	result.blue = (1 - ratio) * obj_color.blue + ratio * amb_color.blue;
	if (result.red > 255)
		result.red = 255;
	if (result.green > 255)
		result.green = 255;
	if (result.blue > 255)
		result.blue = 255;
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
	rt->cy[j].col.red = temp->color.red;
	rt->cy[j].col.green = temp->color.green;
	rt->cy[j].col.blue = temp->color.blue;
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
	rt->pl[j].col.red = temp->color.red;
	rt->pl[j].col.green = temp->color.green;
	rt->pl[j].col.blue = temp->color.blue;
	rt->pl[j].col = apply_ambient(rt->pl[j].col, rt->amb.color, rt->amb.ratio);
}

void	get_sphere(t_minirt *rt, t_arg *temp, int i, int j)
{
	rt->sp[j].id = i;
	rt->sp[j].center.x = temp->coor.x;
	rt->sp[j].center.y = temp->coor.y;
	rt->sp[j].center.z = temp->coor.z;
	rt->sp[j].col.red = temp->color.red;
	rt->sp[j].col.green = temp->color.green;
	rt->sp[j].col.blue = temp->color.blue;
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
