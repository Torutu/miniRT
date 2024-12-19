#include "mini.h"
#include "MLX42/include/MLX42/MLX42.h"

t_ray ray(t_vec3 origin, t_vec3 direction) {
    t_ray r;
    r.origin = origin;
    r.direction = vec3_normalize(direction);
    return r;
}

t_vec3 ray_at(t_ray r, double t) {
    // Position along the ray: origin + t * direction
    return vec3_add(r.origin, vec3_scale(r.direction, t));
}

void render_raytraced_image(mlx_image_t *img) {
    const int image_width = img->width;
    const int image_height = img->height;

    // Camera setup
    t_vec3 camera_origin = vec3(0, 0, 0);
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)image_width / image_height);
    double focal_length = 1.0;

    t_vec3 horizontal = vec3(viewport_width, 0, 0);
    t_vec3 vertical = vec3(0, viewport_height, 0);
    t_vec3 lower_left_corner = vec3_sub(vec3_sub(vec3_sub(camera_origin,
                                   vec3_scale(horizontal, 0.5)),
                                   vec3_scale(vertical, 0.5)),
                                   vec3(0, 0, focal_length));

    // Plane setup
    t_plane plane = create_plane(vec3(0, -1, 0), vec3(0, 1, 0), vec3(1.0, 0.0, 0.0)); // red plane

    for (int y = 0; y < image_height; y++) {
        for (int x = 0; x < image_width; x++) {
            double u = (double)x / (image_width - 1);
            double v = (double)(image_height - 1 - y) / (image_height - 1);

            t_ray r = ray(camera_origin, vec3_sub(vec3_add(vec3_add(lower_left_corner,
                                      vec3_scale(horizontal, u)),
                                      vec3_scale(vertical, v)),
                                      camera_origin));

            t_vec3 pixel_color;
            double t;
            t_vec3 plane_color;

            // Check if the ray hits the plane
            if (hit_plane(&plane, &r, &t, &plane_color)) {
                pixel_color = plane_color; // The plane's color is darkened based on distance
            } else {
                // Background gradient
                t_vec3 unit_direction = vec3_normalize(r.direction);
                t = 0.5 * (unit_direction.y + 1.0);
                pixel_color = vec3_add(vec3_scale(vec3(1.0, 1.0, 1.0), 1.0 - t),
                                       vec3_scale(vec3(0.5, 0.7, 1.0), t));
            }

            // Convert color to RGB
            uint32_t rgb_color = ((uint8_t)(255.999 * pixel_color.x) << 24) | 
                                 ((uint8_t)(255.999 * pixel_color.y) << 16) | 
                                 ((uint8_t)(255.999 * pixel_color.z) << 8) | 0xFF;

            mlx_put_pixel(img, x, y, rgb_color);
        }
    }
}
