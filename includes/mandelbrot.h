#ifndef MANDELBROT_H
# define MANDELBROT_H
# include "fractol.h"
# include <math.h>
# include <stdio.h>

int is_in_mandelbrot(t_complex *c, int max);
double	is_in_mandelbrot_d(t_complex *c, int max);

#endif