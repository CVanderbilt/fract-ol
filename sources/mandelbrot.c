#include "mandelbrot.h"

void	mandelbrot_derivative(t_complex *d, t_complex *prev)
{
	complex_mul(d, prev);
	complex_imul(d, 2);
	d->r++;
}

void	mandelbrot_formula(t_complex *prev, t_complex *c)
{
	complex_pow2(prev);
	complex_add(prev, c);
}

int	is_in_mandelbrot(t_complex *c, int max)
{
	int			i;
	t_complex	prev;

	prev.r = 0;
	prev.i = 0;
	i = -1;
	while (++i < max)
	{
		if (complex_mod_squared(&prev) >= 4)
			return (i);
		mandelbrot_formula(&prev, c);
		if (prev.r == 0 && prev.i == 0)
			return (max);
	}
	return (i);
}

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
		mandelbrot_derivative(&derivative, &prev);
		mandelbrot_formula(&prev, c);
		if (prev.r == 0 && prev.i == 0)
			i = max - 1;
	}
	return (0);
}
