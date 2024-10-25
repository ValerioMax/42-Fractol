/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:42 by valerio           #+#    #+#             */
/*   Updated: 2024/10/25 15:30:37 by valerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//bitwise operation to get the color value in hexadecimale (nella pratica usare define)
int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_r(int rgb)
{
	return ((rgb >> 16) & 0xFF);
}

int	get_g(int rgb)
{
	return ((rgb >> 8) & 0xFF);
}

int	get_b(int rgb)
{
	return (rgb & 0xFF);
}

void my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*((unsigned int *)(img->pixels + offset)) = color;
}

double *linspace(double start, double end, int num)
{
	double	*v = malloc(num * sizeof(double));

	if (start < end)
		for (int i = 0; i < num; i++)
			v[i] = start + (((end - start) / (num - 0)) * i);
	else if (start > end)
		for (int i = 0; i < num; i++)
			v[i] = start - (((start - end) / (num - 0)) * i);
	else
		for (int i = 0; i < num; i++)
			v[i] = start;
	return v;
}

void concat(double *src, double *dst, int i, int len)
{
	for (int k = 0; k < len; k++)
		dst[k + i] = src[k];
}

double **get_palette(double colors[][3], int num_colors) // da rivedere
{
	double **palette = malloc(sizeof(double*) * 3);
	palette[0] = malloc(ITER * sizeof(double));
	palette[1] = malloc(ITER * sizeof(double));
	palette[2] = malloc(ITER * sizeof(double));
	int len = ITER / (num_colors - 1);
	double *r1;
	double *g1;
	double *b1;
	for (int i = 0; i < num_colors - 1; i++)
	{
		r1 = linspace(colors[i][0], colors[i + 1][0], len);
		g1 = linspace(colors[i][1], colors[i + 1][1], len);
		b1 = linspace(colors[i][2], colors[i + 1][2], len);
		concat(r1, palette[0], i * len, len);
		concat(g1, palette[1], i * len, len);
		concat(b1, palette[2], i * len, len);
		free(r1);
		free(g1);
		free(b1);
	}
	return palette;
}

void anti_aliasing(t_img *img) // DA RIVEDERE
{
	char	*pixels2 = malloc(HEIGHT * WIDTH);
	unsigned int	mid;
	int				offset;
	
	for (int i = 1; i < HEIGHT - 1; i++)
	{
		for (int j = 1; j < WIDTH - 1; j++)
		{
			mid = 0;
			offset = (i * img->line_len) + (j * (img->bpp / 8));
			mid += *(img->pixels + offset - 1);
			mid += *(img->pixels + offset + 1);
			mid += *(img->pixels + offset - img->line_len);
			mid += *(img->pixels + offset + img->line_len);
			mid += *(img->pixels + offset - img->line_len - 1);
			mid += *(img->pixels + offset - img->line_len + 1);
			mid += *(img->pixels + offset + img->line_len - 1);
			mid += *(img->pixels + offset + img->line_len + 1);
			*(pixels2 + offset) = mid / 8; //in realtà dovrei calcolare la media dei pixel dell'immagine1 salvandomeli in un immagine2 cosi non si influenzano man mano
		}
	}
	for (int i = 1; i < HEIGHT - 1; i++)
		for (int j = 1; j < WIDTH - 1; j++)
		 {
			offset = (i * img->line_len) + (j * (img->bpp / 8));
			*(img->pixels + offset) = *(pixels2 + offset);
		 }
}

static char	*ft_reverse(char *s)
{
	int	i;
	int	len;
	char	temp;

	len = strlen((const char *) s); // USARE FT_STRLEN DI LIBFT!!
	i = 0;
	while (i < len / 2)
	{
		temp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = temp;
		i++;
	}
	return (s);
}

static long	ft_numlen(long n, int len)
{
	if (n < 0)
		return (ft_numlen(n * -1, len + 1));
	else if (n < 10)
		return (len);
	else
		return (ft_numlen(n / 10, len + 1));
}

static char	*ft_aux(long int n, char *s, int i)
{
	if (n < 10)
	{
		s[i] = n + '0';
		return (s);
	}
	else
	{
		s[i] = n % 10 + '0';
		return (ft_aux(n / 10, s, i + 1));
	}
}

char	*ft_itoa(int n) // DA AGGIUNGERE CON LIBFT INVECE CHE METTERLO QUI
{
	char	*s;
	long	numlen;
	long	long_n;

	long_n = (long int) n;
	numlen = ft_numlen(long_n, 1);
	s = (char *) malloc((numlen + 1) * sizeof(char));
	if (!s)
		return (NULL);
	if (long_n < 0)
	{
		long_n *= -1;
		s[numlen - 1] = '-';
		s[numlen] = '\0';
		s = ft_reverse(ft_aux(long_n, s, 0));
		return (s);
	}
	s[numlen] = '\0';
	return (ft_reverse(ft_aux(long_n, s, 0)));
}

void draw_image(t_data *data, int r, int g , int b)
{
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < WIDTH; j++)
			my_pixel_put(&data->img_new, i, j, create_rgb(r, g, b));
}

int blend_image(t_data *data)
{
	int		r_old, g_old, b_old, r_new, g_new, b_new;
	int		color;
	int		offset;
	int		pixel;
	
	if (data->alpha <= 1)
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				offset = (j * data->img_new.line_len) + (i * (data->img_new.bpp / 8));
				
				pixel = *((unsigned int *)(data->img_old.pixels + offset));
				r_old = get_r(pixel);
				g_old = get_g(pixel);
				b_old = get_b(pixel);
				
				pixel = *((unsigned int *)(data->img_new.pixels + offset));
				r_new = get_r(pixel);
				g_new = get_g(pixel);
				b_new = get_b(pixel);
				
				color = create_rgb(r_new * data->alpha + r_old * (1 - data->alpha), g_new * data->alpha + g_old * (1 - data->alpha),
									b_new * data->alpha + b_old * (1 - data->alpha));
				my_pixel_put(&data->img_old, i, j, color);
			}
		}
	if (data->alpha <= 0.5)
		data->alpha += 0.005;
	usleep(10000);
	mlx_put_image_to_window(data->mlx, data->win, data->img_old.img, 0, 0);
	return 0;
}