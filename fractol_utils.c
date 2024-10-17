/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:48:42 by valerio           #+#    #+#             */
/*   Updated: 2024/10/17 22:48:43 by valerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	encode_rgb(byte red, byte green, byte blue) //bitwise operation to get the color value in hexadecimale (nella pratica usare define)
{
    return (red << 16 | green << 8 | blue);
}

void my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*((unsigned int *)(img->pixels + offset)) = color;
}

float *linspace(float start, float end, int num)
{
	float	*v = malloc(num * sizeof(float));;

	for (int i = 0; i < num; i++)
		v[i] = start + (((end - start) / (num - 0)) * i);
	return v;
}