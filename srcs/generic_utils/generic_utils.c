/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valerio <valerio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:37:53 by valerio           #+#    #+#             */
/*   Updated: 2024/10/25 18:37:59 by valerio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int get_command(char *argv[])
{
	if (!argv || !argv[1] || !strcmp(argv[1], "mandelbrot"))
		return MANDELBROT;
	if (!strcmp(argv[1], "julia"))
		return JULIA;
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
