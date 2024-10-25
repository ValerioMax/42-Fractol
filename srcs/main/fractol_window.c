/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:37 by valerio           #+#    #+#             */
/*   Updated: 2024/10/25 17:49:30 by valerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void fractol_init_window(int ftype)
{
	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Fractol");
	data.img_new.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img_new.pixels = mlx_get_data_addr(data.img_new.img, &data.img_new.bpp, &data.img_new.line_len, &data.img_new.endian);
	data.img_old.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img_old.pixels = mlx_get_data_addr(data.img_old.img, &data.img_old.bpp, &data.img_old.line_len, &data.img_old.endian);
	data.img_mid.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img_mid.pixels = mlx_get_data_addr(data.img_mid.img, &data.img_mid.bpp, &data.img_mid.line_len, &data.img_mid.endian);
	
	data.fractal.ftype = ftype;
	data.semiax = 3;
	data.k = 0.5;
	data.xc = 0;
	data.yc = 0;
	data.alpha = 0;
	data.fractal.iter = 200;
	data.blending = 0;

	double	colors1[][3] = {
								{40, 0, 75},	{110, 225, 70},	{0, 0, 255},
								{230, 200, 80}, {255, 0, 0},
							}; // scrivere una funzione colors_init() che li alloca dinamicamente
	data.palette = get_palette(&data, colors1, 5);

	//print della palette
	/*
	for (int i = 0; i < ITER; i++)
		printf("%d.	%d[%.2f],%d[%.2f],%d[%.2f]\n", i, 	(int)data.palette[0][i], data.palette[0][i],
													 	(int)data.palette[1][i], data.palette[1][i],
													 	(int)data.palette[2][i], data.palette[2][i]);
	*/
	get_fractal(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img_new.img, 0, 0);
	
	if (data.fractal.ftype == JULIA)
		mlx_hook(data.win, 6, (1L<<6), mouse_move_handler, &data);
	mlx_mouse_hook(data.win, mouse_click_handler, &data);
	mlx_key_hook(data.win, key_handler, &data);
	mlx_loop_hook(data.mlx, blend_image, &data);	// fa il blending fra un frame l'altro, però lo fa solo quando non è triggerato alcun evento
													// purtroppo non è possibile farlo nell'hook normale essendo che l'immagine viene renderizzata
													// da mlx_loop solo quando termina la funzione hook
													// (Bisognerebbe implementare una cosa multithread)
	mlx_loop(data.mlx);
}
