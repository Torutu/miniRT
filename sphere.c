#include "includes/main.h"

int intersect_sphere(t_vector origin, t_vector dir, t_sphere sphere, double *t)
{
    t_vector oc = vector_subtract(origin, sphere.center);
    double a = vector_dot(dir, dir);
    double b = 2.0 * vector_dot(oc, dir);
    double c = vector_dot(oc, oc) - sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0)
        return 0;
    else
    {
        *t = (-b - sqrt(discriminant)) / (2.0 * a);
        return 1;
    }
}
