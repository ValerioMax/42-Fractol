/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:46 by valerio           #+#    #+#             */
/*   Updated: 2024/10/19 12:09:35 by valerio          ###   ########.fr       */
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
	return max_iter;
}

void draw_mandelbrot(t_data *data, int max_iter)
{
	int		color;
	int		iter;

	double	*x = linspace(data->xc - data->semiax, data->xc + data->semiax, WIDTH);
	double	*y = linspace(data->yc - data->semiax, data->yc + data->semiax, HEIGHT);

	double	*r = linspace(205, 205, ITER);
	double	*g = linspace(65, 65, ITER);
	double	*b = linspace(75, 205, ITER);
	
	int max = 0;

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			iter = count_iterations(0, 0, x[j], y[i], max_iter);
			//iter = count_iterations(x[j], y[i], -0.7269, 0.1889, max_iter); //Julia set
			//color = encode_rgb(iter, iter, iter);
			//color = encode_rgb(r[iter], g[iter], b[iter]);
			color = encode_rgb(data->palette[0][iter], data->palette[1][iter], data->palette[2][iter]);
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

/*
int main()
{
	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Mandelbrot");
	data.img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img.pixels = mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	data.semiax = 3;
	data.k = 0.5;

	draw_mandelbrot(&data, ITER);

	mlx_key_hook(data.win, handle_input, &data);	//in questo modo viene fatto il draw solo quando c'è un evento (keyPressed)
													//ma avrei potuto usare mlx_loop_hook per fare il draw in modo continuo
	mlx_loop(data.mlx);
}
*/
