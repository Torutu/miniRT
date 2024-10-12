#include "includes/main.h"

t_vector vector_add(t_vector a, t_vector b) {
    return (t_vector){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vector vector_subtract(t_vector a, t_vector b) {
    return (t_vector){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vector vector_scale(t_vector a, double t) {
    return (t_vector){a.x * t, a.y * t, a.z * t};
}

double vector_dot(t_vector a, t_vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double vector_length(t_vector a) {
    return sqrt(vector_dot(a, a));
}

t_vector vector_normalize(t_vector a) {
    double len = vector_length(a);
    return (t_vector){a.x / len, a.y / len, a.z / len};
}
