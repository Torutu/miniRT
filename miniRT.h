/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:40:12 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/14 15:20:54 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <stdio.h> // delete me please

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
	int diameter;
	int pl;
	int cy;
	float height;
	struct s_arg *next;
} t_arg;

typedef struct s_minirt
{
	t_arg	*l_list;
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


/*		MAKING LINKED lIST		*/

void	ft_lstadd_back_rt(t_arg **lst, t_arg *new);

/*		FOR FREEING				*/
void	free_minirt(t_minirt *freeable, char *error);
void	free_split(char **str);

#endif