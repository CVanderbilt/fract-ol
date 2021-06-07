#include "fractol.h"
#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "mandelbrot.h"
#include "julia.h"

int	ft_key_release_hook(int keycode, void *params)
{
	t_controler	*c;

	c = (t_controler *)params;
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

	c = (t_controler *)params;
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
		c->iterations += 10;
	else if (keycode == KEY_O && c->iterations > 50)
		c->iterations -= 10;
	else if (keycode == KEY_ESC)
		return (ft_free_and_exit(params));
	return (0);
}

int	ft_loop_hook(void *params)
{
	t_controler	*c;

	c = (t_controler *)params;
	ft_move(c);
	draw(c);
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, void *param)
{
	t_controler	*c;
	t_complex	p;

	c = (t_controler *)param;
	pixel_to_coo(c, &p, x, y);
	if (button == 5)
	{
		c->scrolling = -1;
		complex_imul(&p, -1);
		move_towards(c, &p);
	}
	if (button == 4)
	{
		c->scrolling = 1;
		move_towards(c, &p);
	}
	if (button == 1)
	{
		c->center.r = 0;
		c->center.i = 0;
		return (0);
	}
	return (0);
}

void	ft_loop(t_controler *c)
{
	t_mlx	*mlx;

	mlx = c->mlx;
	mlx_hook(mlx->window, 2, 1, ft_key_hook, c);
	mlx_hook(mlx->window, 3, 0, ft_key_release_hook, c);
	mlx_hook(mlx->window, 17, 0, ft_free_and_exit, c);
	mlx_mouse_hook(mlx->window, ft_mouse_hook, c);
	mlx_loop_hook(mlx->ptr, ft_loop_hook, c);
	mlx_loop(mlx->ptr);
}
