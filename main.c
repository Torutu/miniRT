/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:45:53 by sataskin          #+#    #+#             */
/*   Updated: 2024/10/16 11:20:16 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char **argv)
{
	t_minirt rt;

	if (argc != 2)
	{
		write(2, "Error\nInvalid arguments. Valid is <./minirt> <filename>", 56);
		exit (1);
	}
	check_valid(argv[1]);
	check_content(argv[1], &rt);
	//execution(&rt);
	//free_everything(&rt);
	return (0);
}