/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:26 by valerio           #+#    #+#             */
/*   Updated: 2024/10/25 15:34:38 by valerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define HEIGHT	500
# define WIDTH	HEIGHT		//(HEIGHT * (((X_MAX - X_MIN) / (Y_MAX - Y_MIN))))
# define ITER	200

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
	t_img	img_new;
	t_img	img_old;
	t_img	img_mid;
	double	xc, yc;
	double	xmin, xmax, ymin, ymax;
	double	semiax; // per zoom
	double	k;		// addendo per spostamento verticale/orizzotale
	double	**palette; //da rimettere a double**

	float	alpha;

}	t_data;

int		create_rgb(int r, int g, int b);
int		get_r(int rgb);
int		get_g(int rgb);
int		get_b(int rgb);
void	my_pixel_put(t_img *img, int x, int y, int color);
double	*linspace(double start, double end, int num);
int 	map(int value, int s0, int e0, int s1, int e1);
double	**get_palette(double colors[][3], int num_colors);
int		**get_palette1(int colors[][3], int num_colors); // prova
void	anti_aliasing(t_img *img); //da vedere
char	*ft_itoa(int num); //DA METTERE CON LBFT!!
void	draw_image(t_data *data, int r, int g , int b);
int		blend_image(t_data *data); //per il loop hook

int		mouse_click_handler(int button, int x, int y, t_data *param);
int		key_handler(int keysym, t_data *data);

int		count_iterations(double zx, double zy, double cx, double cy, int max_iter);
void 	get_mandelbrot(t_data *data, int max_iter);

void 	fractol_init_window();

#endif
