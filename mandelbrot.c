#include "fractol.h"
#include <math.h>
#include <stdio.h>

void	mandelbrot_derivative(t_complex *d, t_complex *prev)
{
	complex_mul(d, prev);
	complex_imul(d, 2);
}

void	mandelbrot_formula(t_complex *prev, t_complex *c)
{
	complex_pow2(prev);
	complex_add(prev, c);
}