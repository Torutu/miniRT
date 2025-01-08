/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:45:53 by sataskin          #+#    #+#             */
/*   Updated: 2025/01/08 07:25:45 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_minirt	rt;

	if (argc != 2)
	{
		write(2, "Error Invalid arguments.", 25);
		write(2, " Valid is <./minirt> <filename>\n", 33);
		exit (1);
	}
	check_valid(argv[1]);
	check_content(argv[1], &rt);
	rt.width = WIDTH;
	rt.height = HEIGHT;
	rt.resizing = 0;
	init_mlx(&rt);
	execution(&rt);
	mlx_loop(rt.mlx);
	mlx_terminate(rt.mlx);
	free_minirt(&rt, "main exit\n");
	return (0);
}
