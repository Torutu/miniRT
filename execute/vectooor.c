#include "../miniRT.h"

// Calculates the length (magnitude) of a 3D vector.
// 
// Parameters:
// a - The 3D vector to calculate the length of.
// 
// Returns:
// The length of the vector as a floating point number.
float	vec_len(t_vec a)
{
	float	len;

	len = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);

	return (len);
}

/**
 * Adds two vectors together.
 *
 * @param a The first vector.
 * @param b The second vector.
 *
 * @return The sum of the two vectors.
 */
t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = b.x + a.x;
	c.y = b.y + a.y;
	c.z = b.z + a.z;

	return (c);
}
/**
 * Returns the negation of a given 3D vector.
 *
 * @param a The input vector to be negated.
 *
 * @return A new vector with the same magnitude as the input 
 * vector, but in the opposite direction.
 */
t_vec	vec_neg(t_vec a)
{
	t_vec	c;

	c.x = -a.x;
	c.y = -a.y;
	c.z = -a.z;

	return (c);
}

/**
 * Subtracts one 3D vector from another.
 *
 * @param a The first vector.
 * @param b The second vector to subtract from the first.
 *
 * @return A new vector that is the difference between the two input vectors.
 */
t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;

	return (c);
}

/**
 * Multiplies a 3D vector by a scalar value.
 *
 * @param a The input 3D vector to be scaled.
 * @param b The scalar value to multiply the vector by.
 *
 * @return A new 3D vector that is the result of the scalar multiplication.
 */
t_vec	vec_mult(t_vec a, float b)
{
	t_vec	c;

	c.x = b * a.x;
	c.y = b * a.y;
	c.z = b * a.z;
    
	return (c);
}
