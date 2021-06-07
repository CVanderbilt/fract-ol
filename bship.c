#include "fractol.h"

void	bship_derivative(t_complex *d, t_complex *prev)
{
	//|prev|^2 - c -> 2|prev|
	complex_mul(d, prev);
	complex_imul(d, 2);
	//d->r++;
}

void	bship_formula(t_complex *prev, t_complex *c)
{
	//|prev|^2 - c
	complex_abs(prev);
	complex_pow2(prev);
	complex_sub(prev, c);
}

int is_in_bship(t_complex *c, int max)
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
		//ft_formula(&prev, c);
		bship_formula(&prev, c);
		if (prev.r == 0 && prev.i == 0)
			return (max);
	}
	return (i);
}
/*
double	is_in_bship_d(t_complex *c, int max)
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
		bship_derivative(&derivative, &prev);
		bship_formula(&prev, c);
		if (prev.r == 0 && prev.i == 0)
			i = max - 1;
	}
	return (0);
}*/