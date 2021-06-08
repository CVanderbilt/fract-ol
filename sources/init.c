#include "fractol.h"
#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "mandelbrot.h"
#include "julia.h"
#include "utils.h"
#include "bship.h"

void	init_mlx(t_mlx *mlx, unsigned int size)
{
	int	line_size;
	int	bpp;
	int	endian;

	mlx->cursor_x = 0;
	mlx->cursor_y = 0;
	mlx->ptr = mlx_init();
	mlx->x = size;
	mlx->y = size;
	mlx->window = mlx_new_window (mlx->ptr, mlx->x, mlx->y, "titulo");
	endian = 1;
	mlx->screen = mlx_new_image (mlx->ptr, mlx->x, mlx->y);
	bpp = 4;
	line_size = mlx->x;
	mlx->screen_data = mlx_get_data_addr (
			mlx->screen, &bpp, &line_size, &endian);
}

void	init_colors(t_controler *controler, int *cmin, int *cmax)
{
	int	a[3];
	int	rgb;
	int	index;

	index = 0;
	while (index < 50)
	{
		a[0] = ((cmax[0] - cmin[0]) / 50 * index + cmin[0]);
		a[1] = ((cmax[1] - cmin[1]) / 50 * index + cmin[1]);
		a[2] = (cmax[2] - cmin[2]) / 50 * index + cmin[2];
		rgb = a[0];
		rgb = (rgb << 8) + a[1];
		rgb = (rgb << 8) + a[2];
		controler->color[index] = rgb;
		index++;
	}
}

void	init_controler(t_controler *controler, t_mlx *m, int *cmin, int *cmax)
{
	init_colors(controler, cmin, cmax);
	complex_init(&controler->center, 0, 0);
	controler->mlx = m;
	controler->radius = 1;
	//controler->mh = 0;
	//controler->mv = 0;
	controler->u = 0;
	controler->d = 0;
	controler->l = 0;
	controler->r = 0;
	controler->mu = 0;
	controler->md = 0;
	controler->ml = 0;
	controler->mr = 0;
	controler->zooming = 0;
	controler->zoom_amount = 0;
	controler->iterations = 50;
	controler->rep = IOO;
}

int	manage_opts(int argc, char *argv[], t_controler *c)
{
	if (argc == 3)
	{
		if (!ft_strcmp(argv[2], "DEM"))
		{
			if (*argv[1] == 'b' || *argv[1] == 'B')
				return (0);
			c->rep = DEM;
		}
		else if (!ft_strcmp(argv[2], "IOO"))
			c->rep = IOO;
		else if (!ft_strcmp(argv[2], "ESC"))
			c->rep = ESC;
		else if (!ft_strcmp(argv[2], "PSY"))
			c->rep = PSY;
		else
			return (0);
	}
	return (1);
}

int	manage_args(int argc, char *argv[], t_controler *c)
{
	if (argc >= 2 && argc <= 3)
	{
		if (*argv[1] == 'M' || *argv[1] == 'm')
		{
			c->is_in_set = is_in_mandelbrot;
			c->is_in_set_d = is_in_mandelbrot_d;
		}
		else if (*argv[1] == 'J' || *argv[1] == 'j')
		{
			c->is_in_set = is_in_julia;
			c->is_in_set_d = is_in_julia_d;
		}
		else if (*argv[1] == 'B' || *argv[1] == 'b')
			c->is_in_set = is_in_bship;
		else
			return (0);
		return (manage_opts(argc, argv, c));
	}
	return (0);
}
