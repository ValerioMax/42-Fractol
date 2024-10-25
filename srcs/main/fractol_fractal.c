/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:46 by valerio           #+#    #+#             */
/*   Updated: 2024/10/25 17:20:19 by valerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int count_iterations(t_data *data, double zx, double zy, double cx, double cy)
{
	double	re;
	double	im;

	for (int i = 0; i < data->fractal.iter; i++)
	{
		re = zx;
		im = zy;
		zx = re * re - im * im + cx;
		zy = 2 * re * im + cy;
		if (sqrt(zx * zx + zy * zy) > 2)
			return i;
	}
	return data->fractal.iter; //oppure ITER - 1
}

void get_mandelbrot(t_data *data)
{
	int		color;
	int		iter;
	double	cx, cy;

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
			iter = count_iterations(data, data->fractal.z0x, data->fractal.z0y, cx, cy); //Mandelbrot set
			//color = encode_rgb(ITER - iter, ITER - iter, ITER - iter);
			color = create_rgb((int) data->palette[0][iter], (int) data->palette[1][iter], (int) data->palette[2][iter]);
			
			my_pixel_put(&data->img_new, j, i, color);
		}
	}
	//anti_aliasing(&data->img); //optional (increase computation)
	//mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void get_julia(t_data *data)
{
	int		color;
	int		iter;
	double	cx, cy;

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
			iter = count_iterations(data, cx, cy, data->fractal.z0x, data->fractal.z0y); //Julia set
			//color = encode_rgb(ITER - iter, ITER - iter, ITER - iter);
			color = create_rgb((int) data->palette[0][iter], (int) data->palette[1][iter], (int) data->palette[2][iter]);
			
			my_pixel_put(&data->img_new, j, i, color);
		}
	}
	//anti_aliasing(&data->img); //optional (increase computation)
	//mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void get_fractal(t_data *data)
{
	if (data->fractal.ftype == MANDELBROT)
		get_mandelbrot(data);
	else if (data->fractal.ftype == JULIA)
		get_julia(data);
}
