#include "fractol.h"
//#include "minilibX/mlx.h"
#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "mandelbrot.h"
#include "julia.h"

#define WHITE 16777215

void	paint_pixel(t_mlx *mlx, char *img, t_complex *c, int color)
{
	int	*aux;

	aux = (int *)img;
	aux[(int)c->r + (int)c->i * mlx->x] = color;
}

int	get_color_dem(t_controler *c, double iter_data)
{
	double	max_distance;
	int		index;

	max_distance = c->radius / c->mlx->x;
	if (iter_data >= max_distance)
		return (c->color[49]);
	if (iter_data <= 0)
		return (c->color[0]);
	index = (int)trunc(iter_data * 50 / max_distance);
	return (c->color[(int)trunc(iter_data * 50 / max_distance)]);
}

int	get_color(t_controler *c, double iter_data)
{
	int	color;
	int	color_d;

	if (c->rep == ESC)
		return (c->color[(int)trunc(50 * iter_data / c->iterations)]);
	else if (c->rep == IOO)
	{
		if ((int)iter_data == (int)c->iterations)
			return (WHITE);
		return (BLACK);
	}
	else if (c->rep == PSY)
	{
		color = 255 - ((int)iter_data * 255 / c->iterations);
		color_d = color;
		color_d = color_d * 1000 + color;
		color_d = color_d * 1000 + color;
		return (mlx_get_color_value(c->mlx, color_d));
	}
	else
		return (get_color_dem(c, iter_data));
}

void	draw(t_controler *c)
{
	int			filas;
	int			columnas;
	t_complex	point;
	t_complex	aux;
	double		iter_data;

	filas = -1;
	while (++filas < c->mlx->y)
	{
		columnas = 0;
		while (columnas < c->mlx->x)
		{
			pixel_to_coo(c, &point, columnas, filas);
			if (c->rep == DEM)
				iter_data = c->is_in_set_d(&point, c->iterations);
			else
				iter_data = c->is_in_set(&point, c->iterations);
			complex_init(&aux, columnas, filas);
			paint_pixel(c->mlx, c->mlx->screen_data, &aux,
				get_color(c, iter_data));
			columnas++;
		}
	}
	mlx_put_image_to_window (c->mlx->ptr, c->mlx->window, c->mlx->screen, 0, 0);
}
