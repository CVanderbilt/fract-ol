#include "fractol.h"
#include <math.h>
#include <stdio.h>

t_complex	*complex_init(t_complex *c, double r, double i)
{
	c->r = r;
	c->i = i;
	return (c);
}

void	complex_pow2(t_complex *t)
{
	double	aux;

	aux = t->r;
	t->r = t->r * t->r - (t->i * t->i);
	t->i = 2 * aux * t->i;
}

void	complex_add(t_complex *d, t_complex *aux)
{
	d->r += aux->r;
	d->i += aux->i;
}

double	complex_mod(t_complex *c)
{
	return (sqrt(c->r * c->r + c->i * c->i));
}

double complex_mod_squared(t_complex *c)
{
	return ((c->r * c->r + c->i * c->i));
}
