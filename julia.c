#include "mandelbrot.h"
#include <unistd.h>

void	julia_derivative(t_complex *d, t_complex *prev)
{
	complex_mul(d, prev);
	complex_imul(d, 2);
}

void	julia_formula(t_complex *prev, t_complex *c)
{
	complex_pow2(prev);
	complex_add(prev, c);
}

int is_in_julia(t_complex *prev, int max)
{
	int i;
	t_complex c;

	complex_init(&c, 0.285, 0.01);
	i = -1;
	while (++i < max)
	{
		if (complex_mod_squared(prev) >= 4)
			return (i);
		julia_formula(prev, &c);
		if (prev->r == 0 && prev->i == 0)
			return (max);
	}
	return (i);
}

double	is_in_julia_d(t_complex *prev, int max)
{
	int			i;
	t_complex	c;
	t_complex	derivative;
	t_complex	start;
	double		mp;

	complex_init(&c, 0.285, 0.01);
	complex_init(&derivative, 1, 0);
	complex_init(&start, prev->r, prev->i);
	i = -1;
	while (++i < max)
	{
		if (complex_mod_squared(prev) >= 4)
		{
			mp = complex_mod(prev);
			return (0.5 * mp * log(mp) / complex_mod(&derivative));
		}
		julia_derivative(&derivative, prev);
		julia_formula(prev, &c);
		if (prev->r == start.r && prev->i == start.i)
			i = max - 1;
	}
	return (0);
}