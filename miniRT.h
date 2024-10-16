/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:40:12 by sataskin          #+#    #+#             */
/*   Updated: 2024/10/16 12:28:47 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft/libft.h"

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

typedef struct s_arg
{
	int A; 
	int l_rat;
	int R;
	int G;
	int B;
	int C;
	int x;
	int y;
	int z;
	int Xnv;
	int Ynv;
	int Znv;
	int FOV;
	int L;
	int bright;
	int sp;
	int diameter;
	int pl;
	int cy;
	int height;
	struct t_arg *next;
} t_arg;

typedef struct s_minirt
{
	t_arg *l_list;
	
} t_minirt;

void	check_content(char *file, t_minirt *rt);
void	check_valid(char *file);

#endif