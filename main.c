/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:45:53 by sataskin          #+#    #+#             */
/*   Updated: 2024/12/30 23:12:01 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
static void printem(t_minirt *rt)
{
	printf("Ambient Light:\n");
    printf("  ID: %d\n", rt->amb.id);
    printf("  Color: (%d, %d, %d)\n", rt->amb.color.R, rt->amb.color.G, rt->amb.color.B);
    printf("  Ratio: %f\n", rt->amb.ratio);

    printf("Camera:\n");
    printf("  ID: %d\n", rt->cam.id);
    printf("  Position: (%f, %f, %f)\n", rt->cam.point.x, rt->cam.point.y, rt->cam.point.z);
    printf("  Orientation Vector: (%f, %f, %f)\n", rt->cam.or_vec.x, rt->cam.or_vec.y, rt->cam.or_vec.z);
    printf("  FOV: %f\n", rt->cam.fov);	

    printf("Light:\n");
    printf("  ID: %d\n", rt->l.id);
    printf("  Point: (%f, %f, %f)\n", rt->l.point.x, rt->l.point.y, rt->l.point.z);
    printf("  Brightness: %f\n", rt->l.bright);
	for(int i = 0; i < rt->pl_count; i++)
	{
	printf("Plane:\n");
    printf("  ID: %d\n", rt->pl[i].id);
    printf("  Point: (%f, %f, %f)\n", rt->pl[i].point.x, rt->pl[i].point.y, rt->pl[i].point.z);
    printf("  Normal: (%f, %f, %f)\n", rt->pl[i].normal.x, rt->pl[i].normal.y, rt->pl[i].normal.z);
    printf("  Color: (%d, %d, %d)\n", rt->pl[i].col.R, rt->pl[i].col.G, rt->pl[i].col.B);
	}
	for (int i = 0; i < rt->sp_count; i++)
	{
	printf("Sphere:\n");
    printf("  ID: %d\n", rt->sp[i].id);
    printf("  Center: (%f, %f, %f)\n", rt->sp[i].center.x, rt->sp[i].center.y, rt->sp[i].center.z);
    printf("  Color: (%d, %d, %d)\n", rt->sp[i].col.R, rt->sp[i].col.G, rt->sp[i].col.B);
    printf("  Diameter: %f\n", rt->sp[i].diameter);
	}
	for (int i = 0; i < rt->cy_count; i++)
	{
	printf("Cylinder:\n");
    printf("  ID: %d\n", rt->cy[i].id);
    printf("  Center: (%f, %f, %f)\n", rt->cy[i].center.x, rt->cy[i].center.y, rt->cy[i].center.z);
    printf("  Axis: (%f, %f, %f)\n", rt->cy[i].axis.x, rt->cy[i].axis.y, rt->cy[i].axis.z);
    printf("  Color: (%d, %d, %d)\n", rt->cy[i].col.R, rt->cy[i].col.G, rt->cy[i].col.B);
    printf("  Diameter: %f, Height: %f\n", rt->cy[i].diameter, rt->cy[i].height);
	}
	}
int	main(int argc, char **argv)
{
	t_minirt rt;

	if (argc != 2)
	{
		write(2, "Error Invalid arguments. Valid is <./minirt> <filename>\n", 56);
		exit (1);
	}
	check_valid(argv[1]);
	check_content(argv[1], &rt);
	printem(&rt);
	//execution(&rt);
	//free_everything(&rt);
	free_minirt(&rt, NULL);
	return (0);
}