#include "fractol.h"
#include <math.h>
#include <stdio.h>

int is_in_mandelbrot(t_complex *c, int max)
{
	int i;
	t_complex prev;

	prev.r = 0;
	prev.i = 0;
	i = -1;
	while (++i < max)
	{
		if (complex_mod_squared(&prev) >= 4)
			return (i);
		complex_pow2(&prev);
		complex_add(&prev, c);
		if (prev.r == 0 && prev.i == 0)
			i = max - 1;
	}
	return (i);
}

//devuelve la distancia hasta el set
double	is_in_mandelbrot_d(t_complex *c, int max)
{
	int			i;
	t_complex	prev;
	t_complex	derivative;
	double		mp;

	prev.r = 0;
	prev.i = 0;
	derivative.i = 0;
	derivative.r = 1;
	i = -1;
	while (++i < max)
	{
		if (complex_mod_squared(&prev) >= 4)
		{
			mp = complex_mod(&prev);
			return (0.5 * mp * log(mp) / complex_mod(&derivative));
		}
		complex_mul(&derivative, &prev);
		complex_imul(&derivative, 2);
		complex_pow2(&prev);
		complex_add(&prev, c);
		derivative.r += 1;
		//derivada *= 2 * prev
		if (prev.r == 0 && prev.i == 0)
			i = max - 1;
	}
	return (0);
}