#include "mini.h"

// Create a plane with a given point and normal
t_plane create_plane(t_vec3 point, t_vec3 normal, t_vec3 color) {
    t_plane plane;
    plane.point = point;
    plane.normal = vec3_normalize(normal); // Ensure the normal is always normalized
    plane.color = color;                   // Assign the color
    return plane;
}


// t_plane create_rotated_plane(t_vec3 point, t_vec3 rotation_angles) {
//     t_vec3 default_normal = vec3(0, 1, 0); // Default normal is upward
//     t_vec3 rotated_normal = rotate_vec3(default_normal, rotation_angles);
//     return create_plane(point, rotated_normal);
// }

//Check if a ray intersects the plane and set the hit color
bool hit_plane(const t_plane *plane, const t_ray *ray, double *t, t_vec3 *color) {
    double denom = vec3_dot(plane->normal, ray->direction);
    // Check if the ray is parallel to the plane
    if (fabs(denom) < 1e-6) {
        return false;
    }
    // Calculate the intersection point (t value)
    t_vec3 p0_to_origin = vec3_sub(plane->point, ray->origin);
    *t = vec3_dot(p0_to_origin, plane->normal) / denom;
    // Check if the intersection is in the positive ray direction
    if (*t > 0) {
        // Adjust color based on distance
        double distance = *t; // The t value is proportional to the distance
        double attenuation = 1.0 / (1.0 + 0.1 * distance); // Example attenuation formula

        // Darken the color based on the distance
        *color = vec3_scale(plane->color, attenuation);
        return true;
    }
    return false;
}
