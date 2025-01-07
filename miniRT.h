/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:40:12 by sataskin          #+#    #+#             */
/*   Updated: 2025/01/07 14:31:03 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "libft/libft.h"
# include <stdio.h> // delete me please

# define MAX_PL 999
# define MAX_SP 999
# define MAX_CY 999

# define WIDTH 120
# define HEIGHT	90
# define PI 3.1415927f

# define RAY_MIN 0.0001f
# define RAY_MAX 1.0e30f

/*
Acceptable values = 000.000 and -000.000
*/
/*
	What each argument in the struct is:
	int A = Ambient Lighting (need below);
	int l_rat = ambient lighting ratio in range [0.0,1.0];
	int red = ed color in range [0-255];
	int green = reen color in range [0-255];
	int blue = lue color in range [0-255];
	
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

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_color
{
	int	red;
	int	blue;
	int	green;
}	t_color;

typedef struct s_ray
{
	float	q;	
	t_vec	start;
	t_vec	direction;
}	t_ray;

typedef struct s_render
{
	t_color	color;
	int		rgba;
	int		x;
	int		y;
	t_vec	px_center;
	t_vec	ray_direction;
	t_ray	ray;
}	t_render;

typedef struct s_hit_info
{
	t_vec	point;
	t_color	color;
	t_vec	normal;
	t_vec	center;
	int		shape;
	int		id;
	float	t;
}	t_hit_info;

typedef struct s_amb
{
	int			id;
	float		ratio;
	t_color		color;
}	t_amb;

typedef struct s_cam
{
	int			id;
	float		fov;
	t_vec		point;
	t_vec		or_vec;
	t_vec		fstpx;
	t_vec		px_size_x;
	t_vec		px_size_y;
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

typedef struct s_init_cam
{
	float		focal_length;
	t_vec		focal;
	t_vec		vport_x;
	t_vec		vport_y;
	t_vec		vport_up_l;
	float		vport_w;
	float		vport_h;
	t_vec		cam_forward;
	t_vec		cam_x_axis;
	t_vec		cam_y_axis;
}	t_init_cam;

typedef struct s_sp_body
{
	t_vec	og_to_cent;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	sqrt_discriminant;
	float	t1;
	float	t2;
}	t_sp_body;

typedef struct s_sp
{
	int		id;
	t_vec	center;
	float	radius;
	t_color	col;
}	t_sp;

typedef struct s_pl
{
	int		id;
	t_vec	point;
	t_vec	normal;
	t_color	col;
}	t_pl;

typedef struct s_count
{
	int	i;
	int	sp;
	int	pl;
	int	cy;
}	t_count;

typedef struct s_cyl_body
{
	float	t_cylinder;
	t_vec	oc;
	t_vec	oc_per;
	t_vec	ray_dir_perp;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	sqrt_discriminant;
	float	t1;
	float	t2;
	t_vec	p1;
	t_vec	p2;
	float	z1;
	float	z2;
}	t_cyl_body;

typedef struct s_cy
{
	int		id;		
	t_vec	center;	
	t_vec	axis;	
	float	radius;	
	float	height;	
	t_color	col;	
}	t_cy;

typedef struct s_arg
{
	int				a;
	float			l_rat;
	t_color			color;
	int				c;
	t_vec			coor;
	t_vec			coor3d;
	int				fov;
	int				l;
	float			bright;
	int				sp;
	float			diameter;
	int				pl;
	int				cy;
	float			height;
	struct s_arg	*next;
}	t_arg;

typedef struct s_minirt
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_arg		*l_list;
	t_amb		amb;
	t_cam		cam;
	t_lit		l;
	t_count		ct;
	t_sp		sp[MAX_SP];
	int			sp_count;
	t_pl		pl[MAX_PL];
	int			pl_count;
	t_cy		cy[MAX_CY];
	int			cy_count;
	char		*line;
	float		aspect_ratio;
	int			width;
	int			height;
	int			resizing;
	int			fd;
}	t_minirt;

void	check_content(char *file, t_minirt *rt);
void	check_valid(char *file);

/*		ADDING VALUES			*/
void	add_ambient(char **values, t_minirt *rt);
void	add_camera(char **values, t_minirt *rt);
void	add_light(char **values, t_minirt *rt);
void	add_sphere(char **values, t_minirt *rt);
void	add_plane(char **values, t_minirt *rt);
void	add_cylinder(char **values, t_minirt *rt);
t_color	apply_ambient(t_color obj_color, t_color amb_color, float ratio);
void	get_cylinder(t_minirt *rt, t_arg *temp, int i, int j);
void	get_plane(t_minirt *rt, t_arg *temp, int i, int j);
void	get_sphere(t_minirt *rt, t_arg *temp, int i, int j);
void	get_light(t_minirt *rt, t_arg *temp, int i);
void	get_cam(t_minirt *rt, t_arg *temp, int i);
void	get_amb(t_minirt *rt, t_arg *temp, int i);

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
int		validate_commas(char *str);

void	execution(t_minirt *rt);

/*		MAKING LINKED lIST		*/

void	ft_lstadd_back_rt(t_arg **lst, t_arg *new);

/*		FOR FREEING				*/
void	free_minirt(t_minirt *freeable, char *error);
void	free_split(char **str);

void	init_mlx(t_minirt *rt);

/*		VECTOOORS				*/
float	vec_len(t_vec a);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_neg(t_vec a);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_mult(t_vec a, float b);
t_vec	vec_div(t_vec a, float b);
float	dot_vec(t_vec a, t_vec b);
t_vec	cross_vec(t_vec a, t_vec b);
t_vec	norm_vec(t_vec v);

/*		RAYS					*/
t_ray	init_ray(t_vec s, t_vec d);
t_vec	ray_point(t_ray r, float t);
t_color	ray_color(t_ray ray, t_minirt rt);
t_vec	calculate_ray_direction(t_vec pixel_center,
			t_vec camera_point, t_vec camera_orient);
t_vec	calculate_pixel_center(t_cam *cam, int x, int y);

/*		UTILS					*/
int		get_rgba(int r, int g, int b, int a);
void	set_px_col(mlx_image_t *img, int x, int y, unsigned int color);

/*		CHECKS					*/
void	check_spheres(t_ray ray, t_minirt rt, t_hit_info *ray_info);
void	check_planes(t_ray ray, t_minirt rt, t_hit_info *ray_info);
void	check_cylinders(t_ray ray, t_minirt rt, t_hit_info *ray_info);
void	check_shadow(t_minirt rt, int *in_shadow, t_hit_info ray_info);

/*		lens					*/
void	calculate_viewport(t_minirt *rt, t_init_cam *i);
void	calculate_camera_axes(t_minirt *rt, t_init_cam *i);
void	calculate_scaled_viewport(t_minirt *rt, t_init_cam *i);
void	calculate_viewport_position(t_minirt *rt, t_init_cam *i);
void	calculate_pixel_origin(t_minirt *rt, t_init_cam *i);

float	hit_cylinder(t_cy c, t_ray ray);
float	hit_sphere(t_vec center, float radius, t_ray ray);
float	hit_plane(t_vec normal, t_vec point, t_ray ray);

t_vec	cyl_normal(t_vec point, t_cy c, float height, float radius);
float	hit_cylinder(t_cy c, t_ray ray);
float	hit_cyl_body(t_ray ray, t_cy c, float r, float h);
float	hit_bot_cap(t_vec axis_dir, t_vec bot_cap_c, t_ray ray, float r);
float	hit_top_cap(t_vec axis_dir, t_vec top_cap_c, t_ray ray, float r);

void	compute_lighting(t_color *color, t_minirt rt, t_hit_info ray_info);

t_color	color_mult(t_color col, float a);
t_color	color_sub(t_color col, float a);
t_color	shadow_mult(t_color col, float a);

#endif