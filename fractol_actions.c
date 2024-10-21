/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:48 by valerio           #+#    #+#             */
/*   Updated: 2024/10/21 21:45:34 by valerio          ###   ########.fr       */
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

	//printf("[%.2f, %.2f] %.4f\n", data->xc, data->yc, data->semiax);
	draw_mandelbrot(data, ITER);
	return 0;
}

int mouse_click_handler(int button, int x, int y, t_data *data)
{
		double	*re = linspace(data->xc - data->semiax, data->xc + data->semiax, WIDTH);
		double	*im = linspace(data->yc - data->semiax, data->yc + data->semiax, HEIGHT);

	if (button == 1) // tasto sinistro
	{
		data->xc = re[x];
		data->yc = im[y];
		
		data->semiax *= 0.75;
		data->k *= 0.75;
		//printf("%d,%d   %d,%d\n", x, y,xc,);
		draw_mandelbrot(data, ITER);
	}
	if (button == 3) // tasto destro
	{
		double cx = re[x];
		double cy = im[y];
		char *s = ft_itoa(count_iterations(0, 0, cx, cy, ITER));
		draw_mandelbrot(data, ITER);
		mlx_string_put(data->mlx, data->win, 30, 30, 0x62F652, s);
		free(s);
	}
	
	return 0;
}


