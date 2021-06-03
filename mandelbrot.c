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
		//if (complex_mod(&prev) >= 2)
		if (complex_mod_squared(&prev) >= 4)
			return (i);
		complex_pow2(&prev);
		complex_add(&prev, c);
	}
	return (i);
}