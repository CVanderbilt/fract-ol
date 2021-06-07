#ifndef JULIA_H
# define JULIA_H
# include "fractol.h"
# include <math.h>
# include <stdio.h>

int is_in_julia(t_complex *c, int max);
double	is_in_julia_d(t_complex *c, int max);

#endif