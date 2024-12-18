#include "mini.h"

t_vec3 vec3(double x, double y, double z) {
    return (t_vec3){x, y, z};
}

t_vec3 vec3_add(t_vec3 a, t_vec3 b) {
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b) {
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

t_vec3 vec3_mul(t_vec3 a, t_vec3 b) {
    return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

t_vec3 vec3_scale(t_vec3 v, double scalar) {
    return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}

double vec3_dot(t_vec3 a, t_vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3 vec3_normalize(t_vec3 v) {
    double length = sqrt(vec3_dot(v, v));
    return vec3_scale(v, 1.0 / length);
}

t_vec3 rotate_vec3(t_vec3 v, t_vec3 rotation) {
    double cos_x = cos(rotation.x), sin_x = sin(rotation.x);
    double cos_y = cos(rotation.y), sin_y = sin(rotation.y);
    double cos_z = cos(rotation.z), sin_z = sin(rotation.z);

    // Rotation around X-axis
    t_vec3 rx = vec3(v.x, v.y * cos_x - v.z * sin_x, v.y * sin_x + v.z * cos_x);

    // Rotation around Y-axis
    t_vec3 ry = vec3(rx.x * cos_y + rx.z * sin_y, rx.y, -rx.x * sin_y + rx.z * cos_y);

    // Rotation around Z-axis
    return vec3(ry.x * cos_z - ry.y * sin_z, ry.x * sin_z + ry.y * cos_z, ry.z);
}
