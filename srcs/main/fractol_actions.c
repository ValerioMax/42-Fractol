/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:48 by valerio           #+#    #+#             */
/*   Updated: 2024/10/25 19:05:06 by valerio          ###   ########.fr       */
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

	if (keysym == XK_b)	// attiva disattiva il blending
		data->blending = 1 - data->blending;

	get_fractal(data);
	if (!data->blending) // renderizza se non è attivo il blending (che renderizza di suo)
		mlx_put_image_to_window(data->mlx, data->win, data->img_new.img, 0, 0);
	return 0;
}

int mouse_click_handler(int button, int x, int y, t_data *data)
{
	//tasto sx: 1, tasto dx: 3, rotella in alto: 4, rotella in basso: 5, rotella click: 2
	if (button == 1) // Si sposta nel punto cliccato
	{
		data->xc = data->xmin + ((data->xmax - data->xmin) / WIDTH) * x;
		data->yc = data->ymin + ((data->ymax - data->ymin) / HEIGHT) * y;
	}
	if (button == 3) // Si sposta e fa zoom nel punto cliccato
	{
		data->xc = data->xmin + ((data->xmax - data->xmin) / WIDTH) * x;
		data->yc = data->ymin + ((data->ymax - data->ymin) / HEIGHT) * y;
		data->semiax *= 0.75;
		data->k *= 0.75;
	}
	if (button == 4) // fa zoom
	{
		data->semiax *= 0.95;
		data->k *= 0.75;
	}
	if (button == 5) // fa dezoom
	{
		data->semiax *= 1.25;
		data->k *= 1.25;
	}
	if (button == 2) // mette a schermo il numero di iterazioni del punto cliccato (da rivedere)
	{
		double cx = data->xmin + ((data->xmax - data->xmin) / WIDTH) * x;
		double cy = data->ymin + ((data->ymax - data->ymin) / HEIGHT) * y;
		char *s = ft_itoa(count_iterations(data, 0, 0, cx, cy));
		get_fractal(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img_new.img, 0, 0);
		mlx_string_put(data->mlx, data->win, 30, 30, 0xffffff, s);
		free(s);
	}
	
	data->alpha = 0;
	get_fractal(data);
	if (!data->blending) // renderizza se non è attivo il blending (che renderizza di suo)
		mlx_put_image_to_window(data->mlx, data->win, data->img_new.img, 0, 0);
	//put on screen HUD (sopra il frame renderizzato)
	return 0;
}

int mouse_move_handler(int x, int y, t_data *data)
{
	data->fractal.z0x = data->xmin + ((data->xmax - data->xmin) / WIDTH) * x;
	data->fractal.z0y= data->ymin + ((data->ymax - data->ymin) / HEIGHT) * y;
	get_fractal(data);
	data->alpha = 0;
	if (!data->blending) // renderizza se non è attivo il blending (che renderizza di suo)
		mlx_put_image_to_window(data->mlx, data->win, data->img_new.img, 0, 0); //se si fa il blending commentarlo
}
