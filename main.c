#include "fractol.h"
#include "minilibX/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#define WHITE 16777215
#define RE_START -2
#define RE_END 1
#define IM_START -1
#define IM_END 1

//pertenece a mandelbrot si Zn >= s^n
//c = 0.4 + 0.3i
//n=0 -> 0 + c = 0.4 + 0.3i
//Z0 >= |c|*2^0 0.4 + 0.3i

int is_in_mandelbrot(t_complex *c, int max);
double	is_in_mandelbrot_d(t_complex *c, int max);

void paint_pixel(t_mlx *mlx, char *img, t_complex *c, int color)
{
	//printf("pinta (%d, %d) = %d\n", (int)c->r, (int)c->i, (int)c->r + (int)c->i * mlx->x);
	int *aux = (int*)img;
	aux[(int)c->r + (int)c->i * mlx->x] = color;
	//printf("painting %d\n", color);
}

int	get_color(t_controler *c, t_complex *point, double iter_data)
{
	if (point)
		point->i = point->i;
	if (c->rep == ESCAPE)
		return (c->color[(int)trunc(50 * iter_data / c->iterations)]);
	else if (c->rep == IN_OR_OUT)
	{
		if ((int)iter_data == (int)c->iterations)
			return (WHITE);
		return (BLACK);
	}
	else if (c->rep == PSY)
	{
		int color = 255 - ((int)iter_data * 255 / c->iterations);
		int color_d = color;
		color_d = color_d * 1000 + color;
		color_d = color_d * 1000 + color;
		return (mlx_get_color_value(c->mlx, color_d));
	}
	else //if (c->rep == DEM)
	{
		//regla de tres con max distance arbitraria
		//distancia relativa a lo que se ve en pantalla (1 / 10 de lo que hay en pantalla)
		double max_distance = c->radius / c->mlx->x;
		//iter_data += max_distance / 50;
		int index;
		//if (c->check)
		//	printf("r: %f, distancia %f, indice %d.", max_distance, iter_data, (int)trunc(iter_data * 50 / max_distance));
		if (iter_data >= max_distance)
		{
			//printf(" ret1 %d.", c->color[49]);
			return (c->color[49]);
		}
		if (iter_data <= 0)
		{
			//printf(" ret2 %d.", c->color[0]);
			return (c->color[0]);
		}
		/*if (iter_data <= 0)
			return (c->color[0]);*/
		//if (iter_data > 0.5)
			//printf("distancia %f, %d\n", iter_data, (int)trunc(iter_data * 50 / max_distance));
		index = (int)trunc(iter_data * 50 / max_distance);
		//if (iter_data > 1)
		//	printf("i: %d\n", index);
		//return ((int)trunc(iter_data * 50 / 5));
		//printf(" ret3 %d.", c->color[index]);
		return (c->color[(int)trunc(iter_data * 50 / max_distance)]);
	}
}

void ft_gra(t_controler *c)
{
	t_complex aux;

	for (int i = 0; i < c->mlx->x; i++)
	{
		for (int j = 0; j < c->mlx->y; j++)
		{
			complex_init(&aux, i, j);
			paint_pixel(c->mlx, c->mlx->screen_data, &aux, c->color[i / (c->mlx->x / 50)]);
			//paint_pixel(c->mlx, c->mlx->screen_data, &aux, c->color[i % 50]);
			//printf("pinta (%d)-> %d\n", i % 50, c->color[i % 50]);
		}
	}
}

void draw(t_controler *c)
{
	int			filas;
	int			columnas;
	t_complex	point;
	t_complex	aux;
	double		iter_data;

	if (c->rep == GRA)
	{
		ft_gra(c);
	}
	else
{
	filas = 0;
	while (filas < c->mlx->y)
	{
		columnas = 0;
		while (columnas < c->mlx->x)
		{
			complex_init(&point, (double)columnas / (double)c->mlx->x * c->radius * 2 -  c->radius + c->center->r,
			(double)filas / (double)c->mlx->y * c->radius * -2 + c->radius + c->center->i);
			if (c->rep == DEM)
				iter_data = is_in_mandelbrot_d(&point, c->iterations);
			else
				iter_data = is_in_mandelbrot(&point, c->iterations);
			complex_init(&aux, columnas, filas);
			/*if (m == (int)c->iterations)
				color_d = 0;
			else
				color_d = c->color[c->iterations % 50];*/
			//paint_pixel(c->mlx, c->mlx->screen_data, &aux, mlx_get_color_value(c->mlx, color_d));
			paint_pixel(c->mlx, c->mlx->screen_data, &aux, get_color(c, &point, iter_data));
			columnas++;
		}
		filas++;
	}
}
	mlx_put_image_to_window (c->mlx->ptr, c->mlx->window, c->mlx->screen, 0, 0);
}

void	ft_move(t_controler *c)
{
	double delta_v;
	double delta_h;
	double delta;

	delta = c->radius / 10;
	delta_v = (c->u - c->d) * delta;
	delta_h = (c->r - c->l) * delta;
	c->center->r += delta_h;
	c->center->i += delta_v;
	if (c->zooming)
	{
		c->zoom_amount++;
		c->radius = c->radius - c->radius /10;
	}
}

int		ft_key_release_hook(int keycode, void *params)
{
	t_controler	*c;

	c = (t_controler*)params;
	if (keycode == KEY_FORWARD)
		c->u = 0;
	if (keycode == KEY_BACKWARD)
		c->d = 0;
	if (keycode == KEY_LEFT)
		c->l = 0;
	if (keycode == KEY_RIGHT)
		c->r = 0;
	if (keycode == KEY_S)
		c->zooming = 0;
	return (0);
}

int	ft_key_hook(int keycode, void *params)
{
	t_controler	*c;

	c = (t_controler*)params;
	if (keycode == KEY_FORWARD)
		c->u = 1;
	else if (keycode == KEY_BACKWARD)
		c->d = 1;
	else if (keycode == KEY_LEFT)
		c->l = 1;
	else if (keycode == KEY_RIGHT)
		c->r = 1;
	else if (keycode == KEY_S)
		c->zooming = 1;
	else if (keycode == KEY_I)
	{
		c->iterations += 10;	
	//	printf("iterations %u\n")
	}
	else if (keycode == KEY_O && c->iterations > 50)
		c->iterations -= 10;
	else if (keycode == KEY_P)
		printf("iterations: %d\n", c->iterations);
	return (0);
}

int		ft_loop_hook(void *params)
{
	t_controler *c;

	c = (t_controler *)params;
	ft_move(c);
	draw(c);
	//getchar();
	//printf("-----------------------------------------\n");
	//printf("-----------------------------------------\n");
	//printf("-----------------------------------------\n");
	c->check = 1;
	return (0);
}

void	ft_loop(t_controler *c)
{
	t_mlx *mlx;

	mlx = c->mlx;
	mlx_hook(mlx->window, 2, 1, ft_key_hook, c);
	mlx_hook(mlx->window, 3, 0, ft_key_release_hook, c);
	//mlx_hook(mlx->window, 17, 0, ft_free_and_exit, data);
	mlx_loop_hook(mlx->ptr, ft_loop_hook, c);
	mlx_loop(mlx->ptr);
}

int main()
{
	t_mlx mlx;
	t_complex center;
	t_controler controler;
	int line_size;
	int bpp;
	int endian;

	mlx.ptr = mlx_init();
	mlx.x = 500;
	mlx.y = 500;
	mlx.window = mlx_new_window (mlx.ptr, mlx.x, mlx.y, "titulo");
	if (!mlx.window)
		printf("error\n");

	endian = 1;
	mlx.screen = mlx_new_image (mlx.ptr, mlx.x, mlx.y);
	bpp = 4;
	line_size = mlx.x;
	mlx.screen_data = mlx_get_data_addr (mlx.screen, &bpp, &line_size, &endian);
	complex_init(&center, 0, 0);
	controler.mlx = &mlx;
	controler.center = &center;
	controler.radius = 1;

	controler.u = 0;
	controler.d = 0;
	controler.l = 0;
	controler.r = 0;
	controler.zooming = 0;
	controler.zoom_amount = 0;
	controler.iterations = 50;

	//color inicial -- color final
	//255 -- 255255255
	int rmin = 0;
	int gmin = 0;
	int bmin = 255;
	int rmax = 255;
	int gmax = 255;
	int bmax = 255;
	for (int i = 0; i < 50; i++)
	{
		//controler.color[i] = mlx_get_color_value(controler.mlx, 255000000 + 5 * i * 1000 + 5 + i);
		int ra = ((rmax - rmin) / 50 * i + rmin);
		int ga = ((gmax - gmin) / 50 * i + gmin);
		int ba = (bmax - bmin) / 50 * i + bmin;
		printf("rgb %d\n", ra + ga + ba);
		int rgb = ra;
		rgb = (rgb << 8) + ga;
		rgb = (rgb << 8) + ba;
		controler.color[i] = (rgb);
		printf("color %d: %d\n", i, controler.color[i]);
	}
	controler.rep = ESCAPE;
//	controler.rep = PSY;
	controler.rep = DEM;
//	controler.rep = IN_OR_OUT;
	controler.check = 0;
	controler.prev_max_distance = 0.6;
	//controler.rep = GRA;
	ft_loop(&controler);
}