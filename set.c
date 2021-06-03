#include "fractol.h"
#include <math.h>
#include <stdio.h>

int is_in_set(t_complex *c, int max,
			void (*ft_formula)(t_complex *, t_complex *))
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
		ft_formula(&prev, c);
		if (prev.r == 0 && prev.i == 0)
			i = max - 1;
	}
	return (i);
}

double	is_in_set_d(t_complex *c, int max, 
			void (*ft_derivative)(t_complex *, t_complex *),
			void (*ft_formula)(t_complex *, t_complex *))
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
		//complex_mul(&derivative, &prev);
		//complex_imul(&derivative, 2);
		ft_derivative(&derivative, &prev);
		ft_formula(&prev, c);
		//complex_pow2(&prev);
		//complex_add(&prev, c);
		derivative.r += 1;
		if (prev.r == 0 && prev.i == 0)
			i = max - 1;
	}
	return (0);
}