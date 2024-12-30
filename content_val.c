/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toru <toru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:42:29 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/30 22:09:06 by toru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void get_cylinder(t_minirt *rt, t_arg *temp, int i, int j)
{
    rt->cy[j].id = i;
    rt->cy[j].center.x = temp->coor.x;
    rt->cy[j].center.y = temp->coor.y;
    rt->cy[j].center.z = temp->coor.z;
    rt->cy[j].axis.x = temp->coor3d.x;
    rt->cy[j].axis.y = temp->coor3d.y;
    rt->cy[j].axis.z = temp->coor3d.z;
    rt->cy[j].diameter = temp->diameter;
    rt->cy[j].height = temp->height;
    rt->cy[j].col.R = temp->color.R;
    rt->cy[j].col.G = temp->color.G;
    rt->cy[j].col.B = temp->color.B;
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
	rt->sp[j].diameter = temp->diameter;
}

static void get_light(t_minirt *rt,t_arg *temp, int i)
{
	rt->l.id = i;
	rt->l.point.x = temp->coor.x;
	rt->l.point.y = temp->coor.y;
	rt->l.point.z = temp->coor.z;
	rt->l.bright = temp->bright;
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
	rt->amb.ratio = temp->l_rat;
}

static void print_ll(t_minirt *rt, t_arg *ll)
{
	t_arg *temp;
	int		i = 0;
	int		sp = 0;
	int		pl = 0;
	int		cy = 0;
	temp = ll;
	while (temp != NULL)
	{
		if (temp->A == 1)
			get_amb(rt, temp, i);
		if (temp->C == 1)
			get_cam(rt, temp, i);
		if (temp->L == 1)
			get_light(rt, temp, i);
		if (temp->sp == 1)
		{
			get_sphere(rt, temp, i, sp);
			sp++;	
		}
		if (temp->pl == 1)
		{
			get_plane(rt, temp, i, pl);
			pl++;
		}
		if (temp->cy == 1)
		{
			get_cylinder(rt, temp, i, cy);
			cy++;
		}
		temp = temp->next;
		i++;
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

static void	get_values(char *line, t_minirt *rt)
{
	char	**values;
	rm_whitespace(line);
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

void check_content(char *file, t_minirt *rt)
{
	rt->fd = open(file, O_RDONLY);
	rt->l_list = NULL;
	rt->line = NULL;
	rt->sp_count = 0;
	rt->pl_count = 0;
	rt->cy_count = 0;
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
		get_values(rt->line, rt);
		free(rt->line);
	}
	print_ll(rt ,rt->l_list);
	close(rt->fd);
	rt->fd = -1;
}
