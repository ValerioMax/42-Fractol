/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:46 by valerio           #+#    #+#             */
/*   Updated: 2024/10/25 15:20:55 by valerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int count_iterations(double zx, double zy, double cx, double cy, int max_iter)
{
	double	re;
	double	im;

	for (int i = 0; i < max_iter; i++)
	{
		re = zx;
		im = zy;
		zx = re * re - im * im + cx;
		zy = 2 * re * im + cy;
		if (sqrt(zx * zx + zy * zy) > 2)
			return i;
	}
	return max_iter; //da cambiare
}

void get_mandelbrot(t_data *data, int max_iter)
{
	int		color;
	int		iter;
	double cx, cy;

	data->xmin = data->xc - data->semiax;
	data->xmax = data->xc + data->semiax;
	data->ymin = data->yc - data->semiax;
	data->ymax = data->yc + data->semiax;
	for (int i = 0; i < HEIGHT; i++)
	{
		cy = data->ymin + ((data->ymax - data->ymin) / HEIGHT)  * i;
		for (int j = 0; j < WIDTH; j++)
		{
			cx = data->xmin + ((data->xmax - data->xmin) / WIDTH)  * j;
			//iter = count_iterations(0, 0, cx, cy, max_iter); //Mandelbrot set
			iter = count_iterations(cx, cy, -0.7269, 0.1889, max_iter); //Julia set
			//color = encode_rgb(ITER - iter, ITER - iter, ITER - iter);
			color = create_rgb((int) data->palette[0][iter], (int) data->palette[1][iter], (int) data->palette[2][iter]);
			
			my_pixel_put(&data->img_new, j, i, color);
		}
	}
	//anti_aliasing(&data->img); //optional (increase computation)
	//mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
