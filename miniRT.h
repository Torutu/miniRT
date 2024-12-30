/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toru <toru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:40:12 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/30 22:25:02 by toru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <stdio.h> // delete me please

# define MAX_PL 999
# define MAX_SP 999
# define MAX_CY 999

/*
Acceptable values = 000.000 and -000.000
*/
/*
	What each argument in the struct is:
	int A = Ambient Lighting (need below);
	int l_rat = ambient lighting ratio in range [0.0,1.0];
	int R = ed color in range [0-255];
	int G = reen color in range [0-255];
	int B = lue color in range [0-255];
	
	int C = Camera (need below);
	int x = coordinate;
	int y = coordinate;
	int z = coordinate;
	int Xnv = 3d normalized orientation vector [-1,1];
	int Ynv = 3d normalized orientation vector [-1,1];
	int Znv = 3d normalized orientation vector [-1,1];
	int FOV = Horizontal field of view [0,180];
	
	int L = Light (need xyz and below);
	int bright = light brightness ratio [0.0,1.0];
	
	int sp = Sphere (need xyz, RGB and below);
	int diameter = sphere diameter;
	
	int pl = Plane (need xyz, XYZnv and RGB);
	
	int cy = Cylinder (need xyz, XYZnv, diameter, RGB and below);
	int height = height;
*/

/*	actors	*/


typedef struct	s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef	struct s_color
{
	int R;
	int B;
	int G;
} t_color;

typedef struct s_ray
{
	float	r;	
	t_vec	start;
	t_vec	direction;
}	t_ray;

typedef struct s_amb
{
	int			id;
	float		ratio;
	t_color		color;
}	t_amb;

typedef struct s_cam
{
	int			id; 	//get_cam
	float		fov;	//get_cam
	t_vec		point;	//get_cam
	t_vec		or_vec;	//get_cam
	t_vec		first_px;
	t_vec		px_delta_u;
	t_vec		px_delta_v;
}	t_cam;

typedef struct s_lit
{
	int		id;
	t_vec	point;
	float	bright;
	t_color	col;
	t_vec	light_dir;
	t_vec	light_color;
	t_vec	lighting;
	t_ray	shadow_ray;
}	t_lit;

typedef struct s_sp
{
	int		id;//get_sphere
	t_vec	center;//get_sphere
	float	diameter;//get_sphere
	t_color	col;//get_sphere
}	t_sp;

typedef struct s_pl
{
	int		id;
	t_vec	point;
	t_vec	normal;
	t_color	col;
}	t_pl;

typedef struct s_cy
{
	int		id;//get_cylinder
	t_vec	center;//get_cylinder
	t_vec	axis;//get_cylinder
	float	diameter;//get_cylinder
	float	height;//get_cylinder
	t_color	col;//get_cylinder
}	t_cy;

typedef struct s_arg
{
	int A; 
	float l_rat;
	t_color color;
	int C;
	t_vec	coor;
	t_vec	coor3d;
	int FOV;
	int L;
	float bright;
	int sp;
	float diameter;
	int pl;
	int cy;
	float height;
	struct s_arg *next;
} t_arg;

typedef struct s_minirt
{
	t_arg	*l_list;
	t_amb	amb;
	t_cam	cam;
	t_lit	l;
	t_sp	sp[MAX_SP];
	int		sp_count;
	t_pl	pl[MAX_PL];
	int		pl_count;
	t_cy	cy[MAX_CY];
	int		cy_count;
	char	*line;
	int		fd;
} t_minirt;

void	check_content(char *file, t_minirt *rt);
void	check_valid(char *file);

/*		ADDING VALUES			*/
void	add_ambient(char **values, t_minirt *rt);
void	add_camera(char **values, t_minirt *rt);
void	add_light(char **values, t_minirt *rt);
void	add_sphere(char **values, t_minirt *rt);
void	add_plane(char **values, t_minirt *rt);
void	add_cylinder(char **values, t_minirt *rt);

/*		PARSING FUNCTIONS		*/
int		argument_count(char **values, int amount);
int		count_commas(char *line);
int		no_extras(char **array);
int		check_nodes(t_arg *nodes, char i);
int		add_colors(char *values, t_arg *new);
int		add_lighting_ratio(char *str, t_arg *new);
int		add_coor(char *values, t_arg *new);
int		add_threed(char *values, t_arg *new);
int		add_horizontal(char *values, t_arg *new);
int		add_diameter(char *str, t_arg *new);
int		val_num(char **val);
int		add_height(char *str, t_arg *new);



/*		MAKING LINKED lIST		*/

void	ft_lstadd_back_rt(t_arg **lst, t_arg *new);

/*		FOR FREEING				*/
void	free_minirt(t_minirt *freeable, char *error);
void	free_split(char **str);

#endif