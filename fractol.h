/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:26 by valerio           #+#    #+#             */
/*   Updated: 2024/10/17 22:48:27 by valerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define HEIGHT	800
# define WIDTH	HEIGHT		//(HEIGHT * (((X_MAX - X_MIN) / (Y_MAX - Y_MIN))))
# define ITER	255 * 3

typedef struct s_img
{
	void	*img; //non so bene a cosa serva
	char	*pixels;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;
	float	xc; //per zoom (da rivedere)
	float	yc; //per zoom (da rivedere)
	float	semiax; // per zoom (da rivedere)
	float	k;
}	t_data;

typedef	unsigned char	byte;

int		encode_rgb(byte red, byte green, byte blue);
void	my_pixel_put(t_img *img, int x, int y, int color);
float	*linspace(float start, float end, int num);

int		key_handler(int keysym, t_data *data);

void 	draw_mandelbrot(t_data *data, int max_iter);

void 	fractol_init_window();

#endif