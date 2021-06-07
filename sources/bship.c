#include "fractol.h"

void	bship_derivative(t_complex *d, t_complex *prev)
{
	complex_mul(d, prev);
	complex_imul(d, 2);
}

void	bship_formula(t_complex *prev, t_complex *c)
{
	complex_abs(prev);
	complex_pow2(prev);
	complex_sub(prev, c);
}

int	is_in_bship(t_complex *c, int max)
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
		bship_formula(&prev, c);
		if (prev.r == 0 && prev.i == 0)
			return (max);
	}
	return (i);
}
