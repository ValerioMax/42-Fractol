/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:37 by valerio           #+#    #+#             */
/*   Updated: 2024/10/19 12:08:07 by valerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void fractol_init_window()
{
	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Mandelbrot");
	data.img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img.pixels = mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	data.semiax = 3;
	data.k = 0.5;
	data.xc = 0;
	data.yc = 0;

	double	colors1[][3] = {	{100, 30, 97}, {0, 0, 255}, {230, 200, 80}, {255, 0, 0}}; // scrivere una funzione colors_init() che li alloca dinamicamente
	double colors[][3] = {	{255, 255, 255}, {255, 0, 0}};
	data.palette = get_palette(colors, 2);

	draw_mandelbrot(&data, ITER);

	mlx_mouse_hook(data.win, mouse_handler, &data);
	mlx_key_hook(data.win, key_handler, &data);	//in questo modo viene fatto il draw solo quando c'è un evento (keyPressed)
												//ma avrei potuto usare mlx_loop_hook per fare il draw in modo continuo
	mlx_loop(data.mlx);
}
