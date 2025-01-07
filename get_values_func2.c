/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values_func2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:14:55 by walnaimi          #+#    #+#             */
/*   Updated: 2025/01/07 14:23:09 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	get_cam(t_minirt *rt, t_arg *temp, int i)
{
	rt->cam.id = i;
	rt->cam.point.x = temp->coor.x;
	rt->cam.point.y = temp->coor.y;
	rt->cam.point.z = temp->coor.z;
	rt->cam.or_vec.x = temp->coor3d.x;
	rt->cam.or_vec.y = temp->coor3d.y;
	rt->cam.or_vec.z = temp->coor3d.z;
	rt->cam.fov = temp->fov;
}

void	get_amb(t_minirt *rt, t_arg *temp, int i)
{
	rt->amb.id = i;
	rt->amb.color.red = temp->color.red;
	rt->amb.color.green = temp->color.green;
	rt->amb.color.blue = temp->color.blue;
	rt->amb.ratio = temp->l_rat / 100;
}
