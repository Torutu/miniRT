#include "includes/main.h"

void render_scene(t_scene *scene, t_vector camera, int width, int height, mlx_image_t *img)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            t_vector dir = {0, 0, -1}; // Simple direction for testing
            double t;
            int color = 0x000000FF; // Default background color

            // Check for sphere intersection
            if (intersect_sphere(camera, dir, scene->spheres[0], &t))
                color = scene->spheres[0].color;

            mlx_put_pixel(img, x, y, color); // Draw pixel in window
        }
    }
}

t_vector get_ray_direction(int x, int y, int width, int height)
{
    double aspect_ratio = (double)width / (double)height;
    double fov = 1.0;
    double screen_x = (2 * ((x + 0.5) / width) - 1) * aspect_ratio * fov;
    double screen_y = (1 - 2 * ((y + 0.5) / height)) * fov;
    t_vector dir = {screen_x, screen_y, -1};
    return vector_normalize(dir);
}
