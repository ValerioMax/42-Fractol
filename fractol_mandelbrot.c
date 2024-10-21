/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:46 by valerio           #+#    #+#             */
/*   Updated: 2024/10/21 21:52:17 by valerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//#define X_MIN	-2.1
//#define X_MAX	0.7
//#define Y_MIN	-1.4
//#define Y_MAX	1.4

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

void draw_mandelbrot(t_data *data, int max_iter)
{
	int		color;
	int		iter;

	double	*x = linspace(data->xc - data->semiax, data->xc + data->semiax, WIDTH);
	double	*y = linspace(data->yc - data->semiax, data->yc + data->semiax, HEIGHT);
	
	int max = 0;

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			iter = count_iterations(0, 0, x[j], y[i], max_iter);
			//iter = count_iterations(x[j], y[i], -0.7269, 0.1889, max_iter); //Julia set
			//color = encode_rgb(ITER - iter, ITER - iter, ITER - iter);
			color = encode_rgb((int) data->palette[0][iter], (int) data->palette[1][iter], (int) data->palette[2][iter]);
			my_pixel_put(&data->img, j, i, color);
			//printf("%d	", iter);
		}
		//printf("\n");
	}
	//anti_aliasing(&data->img); //optional (increase computation)
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	free(x);
	free(y);
}
