#include "fractol.h"
#include <math.h>
#include <stdio.h>

void	complex_mul(t_complex *c, t_complex *m)
{
	t_complex	r;

	r.r = c->r * m->r - c->i * m->i;
	r.i = c->r * m->i + c->i * m->r;
	c->r = r.r;
	c->i = r.i;
}

void	complex_imul(t_complex *c, double m)
{
	c->r *= m;
	c->i *= m;
}

void	complex_abs(t_complex *c)
{
	if (c->i < 0)
		c->i *= -1;
	if (c->r < 0)
		c->r *= -1;
}

void	complex_add(t_complex *d, t_complex *aux)
{
	d->r += aux->r;
	d->i += aux->i;
}

void	complex_sub(t_complex *d, t_complex *aux)
{
	d->r -= aux->r;
	d->i -= aux->i;
}
