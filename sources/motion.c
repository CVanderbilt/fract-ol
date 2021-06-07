#include "fractol.h"

void	ft_move(t_controler *c)
{
	double	delta_v;
	double	delta_h;
	double	delta;

	delta = c->radius / 10;
	delta_v = (c->u - c->d) * delta;
	delta_h = (c->r - c->l) * delta;
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
