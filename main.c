/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:45:53 by sataskin          #+#    #+#             */
/*   Updated: 2025/01/09 14:08:24 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void	free_minirt_main(t_minirt *freeable, char *error)
{
	t_arg	*temp;

	temp = NULL;
	if (freeable->line != NULL)
		free(freeable->line);
	if (error != NULL)
		write(2, error, ft_strlen(error));
	if (freeable->l_list == NULL)
		exit (0);
	if (freeable->l_list != NULL)
	{
		temp = freeable->l_list->next;
		while (freeable->l_list != NULL)
		{
			free(freeable->l_list);
			if (temp == NULL)
				exit(0);
			freeable->l_list = temp;
			temp = temp->next;
		}
	}
	exit(0);
}

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
	free_minirt_main(&rt, "main exit\n");
	return (0);
}
