/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walnaimi <walnaimi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:48:39 by walnaimi          #+#    #+#             */
/*   Updated: 2025/01/09 14:08:24 by walnaimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	set_px_col(mlx_image_t *img, int x, int y, unsigned int color)
{
	int	index;

	index = (y * (int)img->width + x) * 4;
	if (x < (int)img->width && y < (int)img->height)
	{
		img->pixels[index] = (color >> 24) & 0xFF;
		img->pixels[index + 1] = (color >> 16) & 0xFF;
		img->pixels[index + 2] = (color >> 8) & 0xFF;
		img->pixels[index + 3] = color & 0xFF;
	}
}

t_color	color_mult(t_color col, float a)
{
	t_color	new_col;

	new_col.red = col.red * a;
	new_col.green = col.green * a;
	new_col.blue = col.blue * a;
	return (new_col);
}

t_color	shadow_mult(t_color col, float a)
{
	t_color	new_col;

	new_col.red = col.red * a;
	new_col.green = col.green * a;
	new_col.blue = col.blue * a;
	return (new_col);
}

t_color	color_sub(t_color col, float a)
{
	t_color	new_col;

	new_col.red = col.red - a;
	new_col.green = col.green - a;
	new_col.blue = col.blue - a;
	return (new_col);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
