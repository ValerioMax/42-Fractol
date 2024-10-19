/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:26 by valerio           #+#    #+#             */
/*   Updated: 2024/10/19 12:08:52 by valerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define HEIGHT	1000
# define WIDTH	HEIGHT		//(HEIGHT * (((X_MAX - X_MIN) / (Y_MAX - Y_MIN))))
# define ITER	255

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
	double	xc; //per zoom (da rivedere)
	double	yc; //per zoom (da rivedere)
	double	semiax; // per zoom (da rivedere)
	double	k;
	double	**palette;
}	t_data;

typedef	unsigned char	byte;

int		encode_rgb(byte red, byte green, byte blue);
void	my_pixel_put(t_img *img, int x, int y, int color);
double	*linspace(double start, double end, int num);
int 	map(int value, int s0, int e0, int s1, int e1);
double	**get_palette(double colors[][3], int num_colors);
void	anti_aliasing(t_img *img); //da vedere

int		key_handler(int keysym, t_data *data);

void 	draw_mandelbrot(t_data *data, int max_iter);

void 	fractol_init_window();

#endif