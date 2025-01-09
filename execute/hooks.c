/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:46:50 by walnaimi          #+#    #+#             */
/*   Updated: 2025/01/09 14:08:24 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
	rt->img = mlx_new_image(rt->mlx, rt->width, rt->height);
	if (!rt->img)
	{
		mlx_terminate(rt->mlx);
		free_minirt(rt, "mlx new image failed\n");
	}
	if (mlx_image_to_window(rt->mlx, rt->img, 0, 0) == -1)
	{
		mlx_terminate(rt->mlx);
		free_minirt(rt, "mlx image to window failed\n");
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
		free_minirt(rt, "mlx init failed\n");
	}
	rt->img = mlx_new_image(rt->mlx, rt->width, rt->height);
	if (!rt->img)
	{
		mlx_terminate(rt->mlx);
		free_minirt(rt, "mlx new image failed\n");
	}
	if (mlx_image_to_window(rt->mlx, rt->img, 0, 0) == -1)
	{
		mlx_terminate(rt->mlx);
		free_minirt(rt, "mlx image to window failed\n");
	}
	mlx_resize_hook(rt->mlx, &resize_hook, rt);
	mlx_loop_hook(rt->mlx, &resize_done, rt);
	mlx_loop_hook(rt->mlx, &close_hook, rt->mlx);
}
