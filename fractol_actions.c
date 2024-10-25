/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:48 by valerio           #+#    #+#             */
/*   Updated: 2024/10/25 15:19:36 by valerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_handler(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		exit(1);
	if (keysym == XK_i)
	{
		data->semiax *= 0.75;
		data->k *= 0.75;	//scala automaticamente lo spostamento
	}
	if (keysym == XK_o)
	{
		data->semiax *= 1.25;
		data->k *= 1.25;	//scala automaticamente lo spostamento
	}

	if (keysym == XK_k)
		data->k *= 1.25;
	if (keysym == XK_l)
		data->k *= 0.75;

	if (keysym == XK_w)
		data->yc -= data->k;
	if (keysym == XK_a)
		data->xc -= data->k;
	if (keysym == XK_s)
		data->yc += data->k;
	if (keysym == XK_d)
		data->xc += data->k;

	get_mandelbrot(data, ITER);
	mlx_put_image_to_window(data->mlx, data->win, data->img_new.img, 0, 0);
	return 0;
}

int mouse_click_handler(int button, int x, int y, t_data *data)
{
	//tasto sx: 1, tasto dx: 3, rotella in alto: 4, rotella in basso: 5, rotella click: 2
	if (button == 1)
	{
		data->xc = data->xmin + ((data->xmax - data->xmin) / WIDTH) * x;
		data->yc = data->ymin + ((data->ymax - data->ymin) / HEIGHT) * y;
		//data->semiax *= 0.9;
		//data->k *= 0.75;
		data->alpha = 0;
		get_mandelbrot(data, ITER);
		//mlx_put_image_to_window(data->mlx, data->win, data->img_new.img, 0, 0); //se si fa il blending commentarlo
	}
	if (button == 3)
	{
		data->xc = data->xmin + ((data->xmax - data->xmin) / WIDTH) * x;
		data->yc = data->ymin + ((data->ymax - data->ymin) / HEIGHT) * y;
		data->semiax *= 0.75;
		data->k *= 0.75;
		data->alpha = 0;
		get_mandelbrot(data, ITER);
		//mlx_put_image_to_window(data->mlx, data->win, data->img_new.img, 0, 0); //se si fa il blending commentarlo
	}
	if (button == 4)
	{
		data->semiax *= 0.95;
		data->k *= 0.75;
		data->alpha = 0;
		get_mandelbrot(data, ITER);
		//mlx_put_image_to_window(data->mlx, data->win, data->img_new.img, 0, 0); //se si fa il blending commentarlo
	}
	if (button == 5)
	{
		data->semiax *= 1.25;
		data->k *= 1.25;
		data->alpha = 0;
		get_mandelbrot(data, ITER);
	}
	if (button == 2) // tasto destro
	{
		double cx = data->xmin + ((data->xmax - data->xmin) / WIDTH) * x;
		double cy = data->ymin + ((data->ymax - data->ymin) / HEIGHT) * y;
		char *s = ft_itoa(count_iterations(0, 0, cx, cy, ITER));
		get_mandelbrot(data, ITER);
		mlx_put_image_to_window(data->mlx, data->win, data->img_new.img, 0, 0);
		mlx_string_put(data->mlx, data->win, 30, 30, 0xffffff, s);
		free(s);
	}
	
	return 0;
}


