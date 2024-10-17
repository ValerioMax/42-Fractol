/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:48 by valerio           #+#    #+#             */
/*   Updated: 2024/10/17 22:48:49 by valerio          ###   ########.fr       */
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