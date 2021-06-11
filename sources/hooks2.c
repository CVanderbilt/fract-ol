#include "fractol.h"
#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "mandelbrot.h"
#include "julia.h"

static void	reset_motin_vars(t_controler *c)
{
	c->ml = 0;
	c->mr = 0;
	c->mu = 0;
	c->md = 0;
}

int	motion_notify(int x, int y, void *data)
{
	t_controler	*c;

	c = (t_controler *)data;
	mlx_mouse_get_pos(c->mlx->window, &x, &y);
	reset_motin_vars(c);
	if (c->mlx->x / 5 > x)
		c->ml = 1;
	else if (c->mlx->x / 5 * 4 < x)
		c->mr = 1;
	if (c->mlx->y / 5 > y)
		c->mu = 1;
	else if (c->mlx->y / 5 * 4 < y)
		c->md = 1;
	if (x < 0 || x > c->mlx->x)
	{
		c->ml = 0;
		c->mr = 0;
	}
	if (y < 0 || y > c->mlx->y)
	{
		c->mu = 0;
		c->md = 0;
	}
	return (1);
}
