/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:26 by valerio           #+#    #+#             */
/*   Updated: 2024/10/25 18:36:13 by valerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx-linux/mlx.h"
# include <X11/keysym.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

# define HEIGHT	500
# define WIDTH	HEIGHT		//(HEIGHT * (((X_MAX - X_MIN) / (Y_MAX - Y_MIN))))
//# define ITER	200

# define MANDELBROT	1
# define JULIA		2

typedef struct s_img
{
	void	*img; //non so bene a cosa serva
	char	*pixels;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_frct
{
	int		iter;
	int		ftype;
	double	z0x;
	double	z0y;
}	t_frct;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img_new;
	t_img	img_old;
	t_img	img_mid;
	int		blending;
	double	xc, yc;
	double	xmin, xmax, ymin, ymax;
	double	semiax; // per zoom
	double	k;		// addendo per spostamento verticale/orizzotale
	double	**palette; //da rimettere a double**
	float	alpha;
	t_frct	fractal;	
}	t_data;

// image utils
int		create_rgb(int r, int g, int b);
int		get_r(int rgb);
int		get_g(int rgb);
int		get_b(int rgb);
void	my_pixel_put(t_img *img, int x, int y, int color);
double	**get_palette(t_data *data, double colors[][3], int num_colors);
void	anti_aliasing(t_img *img); //da vedere
void	draw_image(t_data *data, int r, int g , int b);
int		blend_image(t_data *data); //per il loop hook

// generic utils
int		get_command(char *argv[]);
int 	map(int value, int s0, int e0, int s1, int e1);
double	*linspace(double start, double end, int num);
char	*ft_itoa(int num); //DA METTERE CON LBFT!!

// events utils
int		mouse_move_handler(int x, int y, t_data *data);
int		mouse_click_handler(int button, int x, int y, t_data *param);
int		key_handler(int keysym, t_data *data);

// computing fractal utils
int		count_iterations(t_data *data, double zx, double zy, double cx, double cy);
void 	get_mandelbrot(t_data *data);
void	get_julia(t_data *data);
void	get_fractal(t_data *data);

void 	fractol_init_window(int ftype);

#endif
