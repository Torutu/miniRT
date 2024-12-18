#ifndef MINI_H
#define MINI_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "MLX42/include/MLX42/MLX42.h"
#define WIDTH 800
#define HEIGHT 600
// Structures
typedef struct s_vec3 {
    double x;
    double y;
    double z;
} t_vec3;

typedef struct s_ray {
    t_vec3 origin;
    t_vec3 direction;
} t_ray;

typedef struct s_plane {
    t_vec3 point;   // A point on the plane
    t_vec3 normal;  // The plane's normal vector
    t_vec3 color;   // Color of the plane
} t_plane;

typedef struct s__ambient_light {
    double strength;   // The intensity of the ambient light (range 0-1)
    t_vec3 color;      // Color of the ambient light
} t_ambient_light;

typedef struct s_point_light{
    t_vec3 position;   // Position of the light in 3D space
    double strength;    // Intensity of the light
} t_point_light;


// Function prototypes
t_vec3 vec3(double x, double y, double z);
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_mul(t_vec3 a, t_vec3 b);
t_vec3 vec3_scale(t_vec3 v, double scalar);
double vec3_dot(t_vec3 a, t_vec3 b);
t_vec3 vec3_normalize(t_vec3 v);
t_vec3 rotate_vec3(t_vec3 v, t_vec3 rotation);
t_ray ray(t_vec3 origin, t_vec3 direction);
t_vec3 ray_at(t_ray r, double t);
void render_raytraced_image(mlx_image_t *img);
//int hit_plane(const t_plane *plane, const t_ray *ray, double *t);
t_plane create_plane(t_vec3 point, t_vec3 normal, t_vec3 color);
bool hit_plane(const t_plane *plane, const t_ray *ray, double *t, t_vec3 *hit_color);

#endif