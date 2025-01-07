/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:42:29 by sataskin          #+#    #+#             */
/*   Updated: 2025/01/07 12:32:39 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


static t_color apply_ambient(t_color obj_color, t_color amb_color, float ratio)
{
    t_color result;

	if (amb_color.R == 255 && amb_color.G == 255 && amb_color.B == 255)
    	return obj_color;

	ratio *= 85;
    result.R = (1 - ratio) * obj_color.R + ratio * amb_color.R;
    result.G = (1 - ratio) * obj_color.G + ratio * amb_color.G;
    result.B = (1 - ratio) * obj_color.B + ratio * amb_color.B;

    // Clamp values to [0, 255]
    result.R = result.R > 255 ? 255 : result.R;
    result.G = result.G > 255 ? 255 : result.G;
    result.B = result.B > 255 ? 255 : result.B;

    return result;
}




static void get_cylinder(t_minirt *rt, t_arg *temp, int i, int j)
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

static void get_plane(t_minirt *rt, t_arg *temp, int i, int j)
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

static void get_sphere(t_minirt *rt, t_arg *temp, int i, int j)
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

static void get_light(t_minirt *rt,t_arg *temp, int i)
{
	rt->l.id = i;
	rt->l.point.x = temp->coor.x;
	rt->l.point.y = temp->coor.y;
	rt->l.point.z = temp->coor.z;
	rt->l.bright = temp->bright/100;
}

static void get_cam(t_minirt *rt,t_arg *temp, int i)
{
	rt->cam.id = i;
	rt->cam.point.x = temp->coor.x;
	rt->cam.point.y = temp->coor.y;
	rt->cam.point.z = temp->coor.z;
	rt->cam.or_vec.x = temp->coor3d.x;
	rt->cam.or_vec.y = temp->coor3d.y;
	rt->cam.or_vec.z = temp->coor3d.z;
	rt->cam.fov = temp->FOV;
}

static void	get_amb(t_minirt *rt,t_arg *temp, int i)
{
	rt->amb.id = i;
	rt->amb.color.R = temp->color.R;
	rt->amb.color.G = temp->color.G;
	rt->amb.color.B = temp->color.B;
	rt->amb.ratio = temp->l_rat/100;
}

static void get_values(t_minirt *rt, t_arg *ll)
{
	t_arg *temp;
	// int		i = 0;
	// int		sp = 0;
	// int		pl = 0;
	// int		cy = 0;
	temp = ll;
	while (temp != NULL)
	{
		if (temp->A == 1)
			get_amb(rt, temp, rt->ct.i);
		if (temp->C == 1)
			get_cam(rt, temp, rt->ct.i);
		if (temp->L == 1)
			get_light(rt, temp, rt->ct.i);
		if (temp->sp == 1)
		{
			get_sphere(rt, temp, rt->ct.i, rt->ct.sp);
			rt->ct.sp++;	
		}
		if (temp->pl == 1)
		{
			get_plane(rt, temp, rt->ct.i, rt->ct.pl);
			rt->ct.pl++;
		}
		if (temp->cy == 1)
		{
			get_cylinder(rt, temp, rt->ct.i, rt->ct.cy);
			rt->ct.cy++;
		}
		temp = temp->next;
		rt->ct.i++;
	}
}

static void	rm_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] != '\0')
	{
		if (line[i] == '\t')
			line[i] = ' ';
		if (line[i] == '\n')
			line[i] = ' ';
		i++;
	}
}

static void	add_values(char *line, t_minirt *rt)
{
	char	**values;
	rm_whitespace(line);
	if (validate_commas(rt->line) == 1)
		free_minirt(rt, "ERROR: Invalid Input in file\n");
	values = ft_split(line, ' ');
	if (!values)
		free_minirt(rt, "Error: MALLOC FAIL\n");
	if (ft_strcmp(values[0], "A") == 0)
		add_ambient(values, rt);
	else if (ft_strcmp(values[0], "C") == 0)
		add_camera(values, rt);
	else if (ft_strcmp(values[0], "L") == 0)
		add_light(values, rt);
	else if (ft_strcmp(values[0], "sp") == 0)
		add_sphere(values, rt);
	else if (ft_strcmp(values[0], "pl") == 0)
		add_plane(values, rt);
	else if (ft_strcmp(values[0], "cy") == 0)
		add_cylinder(values, rt);
	else
		free_minirt(rt, "ERROR: Invalid Input in FILE\n");
	free_split(values);
}

static	void init_struct(t_minirt *rt)
{
	rt->l_list = NULL;
	rt->line = NULL;
	rt->sp_count = 0;
	rt->pl_count = 0;
	rt->cy_count = 0;
	rt->ct.sp = 0;
	rt->ct.pl = 0;
	rt->ct.cy = 0;
	rt->ct.i = 0;
}

void check_content(char *file, t_minirt *rt)
{
	rt->fd = open(file, O_RDONLY);

	init_struct(rt);
	while (1)
	{
		rt->line = get_next_line(rt->fd);
		if (!rt->line)
			break;
		if (!ft_strcmp(rt->line, "\n"))
		{
			free(rt->line);
			continue ;
		}

		add_values(rt->line, rt);
		free(rt->line);
	}
	if (rt->l_list == NULL)
		free_minirt(rt, "ERROR: Empty File\n");
	get_values(rt ,rt->l_list);
	close(rt->fd);
	rt->fd = -1;
}
