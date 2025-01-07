/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:42:29 by sataskin          #+#    #+#             */
/*   Updated: 2025/01/07 14:43:37 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// static void	get_values(t_minirt *rt, t_arg *ll)
// {
// 	t_arg *temp;

// 	temp = ll;
// 	while (temp != NULL)
// 	{
// 		if (temp->a == 1)
// 			get_amb(rt, temp, rt->ct.i);
// 		if (temp->c == 1)
// 			get_cam(rt, temp, rt->ct.i);
// 		if (temp->l == 1)
// 			get_light(rt, temp, rt->ct.i);
// 		if (temp->sp == 1)
// 		{
// 			get_sphere(rt, temp, rt->ct.i, rt->ct.sp++);
// 			rt->ct.sp++;	
// 		}
// 		if (temp->pl == 1)
// 		{
// 			get_plane(rt, temp, rt->ct.i, rt->ct.pl++);
// 			rt->ct.pl++;
// 		}
// 		if (temp->cy == 1)
// 		{
// 			get_cylinder(rt, temp, rt->ct.i, rt->ct.cy++);
// 			rt->ct.cy++;
// 		}
// 		temp = temp->next;
// 		rt->ct.i++;
// 	}
// }

static void	get_values(t_minirt *rt, t_arg *ll)
{
	t_arg	*temp;

	temp = ll;
	while (temp != NULL)
	{
		if (temp->a == 1)
			get_amb(rt, temp, rt->ct.i);
		if (temp->c == 1)
			get_cam(rt, temp, rt->ct.i);
		if (temp->l == 1)
			get_light(rt, temp, rt->ct.i);
		if (temp->sp == 1)
			get_sphere(rt, temp, rt->ct.i, rt->ct.sp++);
		if (temp->pl == 1)
			get_plane(rt, temp, rt->ct.i, rt->ct.pl++);
		if (temp->cy == 1)
			get_cylinder(rt, temp, rt->ct.i, rt->ct.cy++);
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

static void	init_struct(t_minirt *rt)
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

void	check_content(char *file, t_minirt *rt)
{
	rt->fd = open(file, O_RDONLY);
	init_struct(rt);
	while (1)
	{
		rt->line = get_next_line(rt->fd);
		if (!rt->line)
			break ;
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
	get_values(rt, rt->l_list);
	close(rt->fd);
	rt->fd = -1;
}
