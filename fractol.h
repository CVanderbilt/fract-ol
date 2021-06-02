#ifndef	FRACTOL_H
# define FRACTOL_H

# define LEFT_CLICK 	1
# define RIGHT_CLICK 	2
# define MIDDLE_CLICK	3
# define SCROLL_UP		4
# define SCROLL_DOWN	5

# define KEY_1			18
# define KEY_2			19
# define KEY_3			20
# define KEY_4			21
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_I			34
# define KEY_O			31
# define KEY_P			35
# define KEY_J			38
# define KEY_K			40
# define KEY_L			37
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_FORWARD 	126
# define KEY_BACKWARD	125

# define KEY_TAB	48
# define KEY_MAJ	257
# define KEY_ESC	53
# define KEY_TAB	48

typedef struct		s_mlx
{
	void		*ptr;
	void		*window;
	void		*screen;
	char		*screen_data;
	char		*title;
	int			x;
	int			y;
}	t_mlx;

typedef struct	s_complex
{
	double	r;
	double	i;
}	t_complex;

typedef struct	s_controler
{
	t_mlx		*mlx;
	t_complex	*center;
	double		radius;

	int	u;
	int	d;
	int	l;
	int	r;
	int	zooming;
	int base_color;

	int max_count;
	int zoom_amount;
}	t_controler;

void		complex_pow2(t_complex *t);
void		complex_add(t_complex *d, t_complex *aux);
double		complex_mod(t_complex *c);
t_complex	*complex_init(t_complex *c, double r, double i);


#endif