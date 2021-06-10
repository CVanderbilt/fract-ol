#include "fractol.h"
//#include "minilibX/mlx.h"
#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include "mandelbrot.h"
#include "julia.h"
#include "bship.h"
#include "utils.h"

void	pixel_to_coo(t_controler *c, t_complex *point, int x, int y)
{
	complex_init(point,
		(double)x / (double)c->mlx->x * c->radius * 2 - c->radius + c->center.r,
		(double)y / (double)c->mlx->y * c->radius * -2
		+ c->radius + c->center.i);
}

int	ft_free_and_exit(void *param)
{
	t_controler	*c;

	c = (t_controler *)param;
	c->base_color = 0;
	exit(0);
	return (0);
}

void	ft_help(t_controler *c)
{
	write(1, "Wrong parameters\n", 17);
	write(1, "./fract-ol [type] (render_method)\n", 34);
	write(1, "types: 'mandelbrot', 'julia', 'ship'\n", 37);
	write(1, "render methods: IOO(default), DEM(not av", 40);
	write(1, "ailable for burning ship), PSY and ESC\n", 39);
	ft_free_and_exit(c);
}

int	main(int argc, char *argv[])
{
	t_mlx		mlx;
	t_controler	controler;
	int			min[3];
	int			max[3];

	min[0] = 0;
	min[1] = 0;
	min[2] = 0;
	max[0] = 255;
	max[1] = 100;
	max[2] = 255;
	init_controler(&controler, &mlx, min, max);
	if (!manage_args(argc, argv, &controler))
		ft_help(&controler);
	init_mlx(&mlx, 500);
	ft_loop(&controler);
}
