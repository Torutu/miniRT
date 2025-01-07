/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:46:39 by walnaimi          #+#    #+#             */
/*   Updated: 2025/01/07 11:56:01 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

/*
 * Helper function explanations:
 * 
 **- calculate_perp_comp:
 *   This function calculates the perpendicular components of
 *   the ray's origin and direction relative to the cylinder's axis. 
 *   These components are essential for determining the ray's
 *   interaction with the cylindrical surface.
 *
 **- calculate_quadratic_coefficients:
 *   This function computes the quadratic coefficients (a, b, c) 
 *   that are required to solve the quadratic equation 
 *   for the ray-cylinder intersection. These coefficients
 *   are derived from the ray's parametric equation 
 *   and the cylinder's implicit equation.
 *
 **- calculate_two_intersections:
 *   This function determines the two potential intersection
 *   points (`t1` and `t2`) by solving the quadratic equation.
 *   It also ensures that if there is no valid intersection
 *   (negative discriminant), the values are set to -1.0.
 *
 **- calculate_intersection_points:
 *   This function calculates the exact intersection points
 *   (`p1` and `p2`) of the ray with the cylinder's infinite surface
 *   and determines their z-values relative to the cylinder's axis,
 *   which are used to verify if the intersections lie 
 *   within the finite height of the cylinder.
 *
 **- hit_cyl_body:
 *   This is the main function that combines all the above
 *   helper functions to determine the closest valid 
 *   intersection point of a ray with a finite-height
 *   cylinder. If no intersection occurs, it returns -1.0.
 */

static	void	calculate_perp_comp(t_ray ray, t_cy c, t_cyl_body *cy)
{
	cy->oc = vec_sub(ray.start, c.center);
	cy->oc_per = vec_sub(cy->oc, vec_mult(c.axis, dot_vec(cy->oc, c.axis)));
	cy->ray_dir_perp = vec_sub(ray.direction,
			vec_mult(c.axis, dot_vec(ray.direction, c.axis)));
}

static	void	calculate_quadratic_coefficients(t_cyl_body *cy, float r)
{
	cy->a = dot_vec(cy->ray_dir_perp, cy->ray_dir_perp);
	cy->b = 2.0f * dot_vec(cy->ray_dir_perp, cy->oc_per);
	cy->c = dot_vec(cy->oc_per, cy->oc_per) - r * r;
}

static	void	calculate_two_intersections(t_cyl_body *cy)
{
	cy->discriminant = cy->b * cy->b - 4.0f * cy->a * cy->c;
	if (cy->discriminant >= 0.0f)
	{
		cy->sqrt_discriminant = sqrtf(cy->discriminant);
		cy->t1 = (-cy->b - cy->sqrt_discriminant) / (2.0f * cy->a);
		cy->t2 = (-cy->b + cy->sqrt_discriminant) / (2.0f * cy->a);
	}
	else
	{
		cy->t1 = -1.0f;
		cy->t2 = -1.0f;
	}
}

static	void	calculate_intersection_points(t_ray ray, t_cy c, t_cyl_body *cy)
{
	cy->p1 = vec_add(ray.start, vec_mult(ray.direction, cy->t1));
	cy->p2 = vec_add(ray.start, vec_mult(ray.direction, cy->t2));
	cy->z1 = dot_vec(vec_sub(cy->p1, c.center), c.axis);
	cy->z2 = dot_vec(vec_sub(cy->p2, c.center), c.axis);
}

float	hit_cyl_body(t_ray ray, t_cy c, float r, float h)
{
	t_cyl_body	cy;

	calculate_perp_comp(ray, c, &cy);
	calculate_quadratic_coefficients(&cy, r);
	calculate_two_intersections(&cy);
	if (cy.discriminant < 0.0f)
		return (-1.0f);
	calculate_intersection_points(ray, c, &cy);
	cy.t_cylinder = -1.0f;
	if (cy.t1 > 0 && cy.z1 >= -h / 2.0f && cy.z1 <= h / 2.0f)
		cy.t_cylinder = cy.t1;
	else if (cy.t2 > 0 && cy.z2 >= -h / 2.0f && cy.z2 <= h / 2.0f)
		cy.t_cylinder = cy.t2;
	return (cy.t_cylinder);
}
