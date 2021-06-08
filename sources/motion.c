#include "fractol.h"

double	get_delta(t_controler *c, int n, double delta)
{
	int	u;
	int	d;
	int	diff;

	u = c->u;
	d = c->d;
	if (n == 1)
	{
		u = c->r;
		d = c->l;
	}
	diff = u - d;
	if (diff == 0)
	{
		diff = c->mu - c->md;
		if (n == 1)
			diff = c->mr - c->ml;
	}
	return (diff * delta);
}

void	ft_move(t_controler *c)
{
	double	delta_v;
	double	delta_h;
	double	delta;

	delta = c->radius / 10;
	delta_v = get_delta(c, 0, delta);
	delta_h = get_delta(c, 1, delta);
	c->center.r += delta_h;
	c->center.i += delta_v;
	if (c->zooming || c->scrolling)
	{
		if (c->scrolling < 0)
		{
			c->zoom_amount--;
			c->radius = c->radius + c->radius / 10;
		}
		else
		{
			c->zoom_amount++;
			c->radius = c->radius - c->radius / 10;
		}
		c->scrolling = 0;
	}
}

void	move_towards(t_controler *c, t_complex *point)
{
	double		delta;
	double		hdiff;
	double		vdiff;
	t_complex	mov;

	complex_init(&mov, 0, 0);
	hdiff = point->r - c->center.r;
	vdiff = point->i - c->center.i;
	delta = c->radius / 10;
	if (hdiff > delta)
		hdiff = delta;
	else if (hdiff < -delta)
		hdiff = -delta;
	if (vdiff > delta)
		vdiff = delta;
	else if (vdiff < -delta)
		vdiff = -delta;
	c->center.r += hdiff;
	c->center.i += vdiff;
}
