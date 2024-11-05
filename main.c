/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:45:53 by sataskin          #+#    #+#             */
/*   Updated: 2024/11/05 14:43:46 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "miniRT.h"

// int	main(int argc, char **argv)
// {
// 	t_minirt rt;

// 	if (argc != 2)
// 	{
// 		write(2, "Error\nInvalid arguments. Valid is <./minirt> <filename>\n", 56);
// 		exit (1);
// 	}
// 	check_valid(argv[1]);
// 	check_content(argv[1], &rt);
// 	//execution(&rt);
// 	//free_everything(&rt);
// 	return (0);
// }

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_minirt rt;

	if (argc != 2)
	{
		write(2, "Error\nInvalid arguments. Valid is <./minirt> <filename>\n", 56);
		exit(1);
	}

	// Check the validity of the file
	check_valid(argv[1]);
	check_content(argv[1], &rt);

	// Initialize the MLX window
	rt.mlx = mlx_init(800, 600, "miniRT", true);
	if (!rt.mlx)
	{
		write(2, "Error\nFailed to initialize MLX\n", 31);
		exit(1);
	}

	// Main render loop
	mlx_loop(rt.mlx);

	// Free the resources and close the window
	mlx_terminate(rt.mlx);

	return (0);
}
