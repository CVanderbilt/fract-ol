#include "fractol.h"
#include <mlx.h>
#include <stdio.h>

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

void paint_pixel(t_mlx *mlx, char *img, t_complex *c, int color)
{
	//printf("pinta (%d, %d) = %d\n", (int)c->r, (int)c->i, (int)c->r + (int)c->i * mlx->x);
	int *aux = (int*)img;
	aux[(int)c->r + (int)c->i * mlx->x] = color;
}

void draw(t_controler *c)
{
	t_complex	aux;
	int			filas;
	int			columnas;

	filas = 0;
	while (filas < c->mlx->y)
	{
		columnas = 0;
		while (columnas < c->mlx->x)
		{
			//double real = (double)columnas / (double)mlx->x * tramo_horizontal - tramo_horizontal / 2 + center.r;
			//double imaginario = (double)filas / (double)mlx->y * -tramo_vertical + tramo_vertical / 2 + center.i;
			double real = (double)columnas / (double)c->mlx->x * c->radius * 2 -  c->radius + c->center->r;
			double imaginario = (double)filas / (double)c->mlx->y * c->radius * -2 + c->radius + c->center->i;
			complex_init(&aux, real, imaginario);
			c->max_count = 80 + c->zoom_amount / 10;
			int m = is_in_mandelbrot(&aux, c->max_count);
			int color = 255 - (m * 255 / c->max_count);
			int color_d = color;
			color_d = color_d * 1000 + color;
			color_d = color_d * 1000 + color;
			//c->base_color = mlx_get_color_value(c->mlx->ptr, 255255255) / c->radius;
			//int m = is_in_mandelbrot(&aux, 80);
			//if (is_in_mandelbrot(&aux, 80))
			
			{
				complex_init(&aux, columnas, filas);
				paint_pixel(c->mlx, c->mlx->screen_data, &aux, mlx_get_color_value(c->mlx, color_d));
			}
			columnas++;
		}
		filas++;
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
	if (keycode == KEY_BACKWARD)
		c->d = 1;
	if (keycode == KEY_LEFT)
		c->l = 1;
	if (keycode == KEY_RIGHT)
		c->r = 1;
	if (keycode == KEY_S)
		c->zooming = 1;

	return (0);
}

int		ft_loop_hook(void *params)
{
	t_controler *c;

	c = (t_controler *)params;
	ft_move(c);
	draw(c);
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
	mlx.x = 1000;
	mlx.y = 1000;
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
	ft_loop(&controler);
}