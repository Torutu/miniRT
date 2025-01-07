/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:46:50 by walnaimi          #+#    #+#             */
/*   Updated: 2025/01/07 12:06:52 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

static	void	resize_done(void *param)
{
	t_minirt	*rt;

	rt = param;
	if (rt->resizing)
	{
		rt->resizing = 0;
		execution(rt);
	}
}

static	void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_minirt	*rt;

	rt = param;
	rt->resizing = 1;
	rt->width = width;
	rt->height = height;
	if (rt->img)
		mlx_delete_image(rt->mlx, rt->img);
	rt->img = mlx_new_image(rt->mlx, width, height);
	if (!rt->img)
	{
		printf("Failed to resize the image buffer\n");
		exit(1);
	}
	if (mlx_image_to_window(rt->mlx, rt->img, 0, 0) == -1)
	{
		printf("Failed to attach resized image to window\n");
		exit(1);
	}
}

static	void	close_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	init_mlx(t_minirt *rt)
{
	rt->mlx = mlx_init(rt->width, rt->height, "mmm yes minirt", true);
	if (!rt->mlx)
	{
		printf("mlx_init failed\n");
		exit(1);
	}
	rt->img = mlx_new_image(rt->mlx, rt->width, rt->height);
	if (!rt->img)
	{
		printf("mlx_new_image failed\n");
		exit(1);
	}
	if (mlx_image_to_window(rt->mlx, rt->img, 0, 0) == -1)
	{
		printf("mlx_image_to_window failed\n");
		exit(1);
	}
	mlx_resize_hook(rt->mlx, &resize_hook, rt);
	mlx_loop_hook(rt->mlx, &resize_done, rt);
	mlx_loop_hook(rt->mlx, &close_hook, rt->mlx);
}
