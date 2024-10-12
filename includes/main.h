#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../MLX42/include/MLX42/MLX42.h"

// Window dimensions
#define WIDTH 800
#define HEIGHT 600

// VECTOR
typedef struct s_vector 
{
    double x;
    double y;
    double z;
} t_vector;

// Vector functions
t_vector vector_add(t_vector a, t_vector b);
t_vector vector_subtract(t_vector a, t_vector b);
t_vector vector_scale(t_vector a, double t);
double vector_dot(t_vector a, t_vector b);
double vector_length(t_vector a);
t_vector vector_normalize(t_vector a);

// SHAPES
typedef struct s_sphere
{
    t_vector center;
    double radius;
    int color;
} t_sphere;

// Raytracing
typedef struct s_scene
{
    t_sphere *spheres;
    int sphere_count;
} t_scene;

typedef struct s_data 
{
    mlx_t *mlx;
    mlx_image_t *img;
} t_data;

// Rendering and raytracing functions
void render_scene(t_scene *scene, t_vector camera, int width, int height, mlx_image_t *img);
t_vector get_ray_direction(int x, int y, int width, int height);

// Sphere intersection
int intersect_sphere(t_vector origin, t_vector dir, t_sphere sphere, double *t);

#endif // MAIN_H
