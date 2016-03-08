/*
** raytracer.h for rt
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:26:01 2016 marc brout
** Last update Tue Mar  8 22:39:09 2016 marc brout
*/

#ifndef RAYTRACER_H_
# define RAYTRACER_H_

# define GET_F bunny_ini_scope_get_field
# define UNUSED __attribute__((__unused__))
# define NO_FILE ".ini file can't be opened.\n"
# define USAGE "Usage: ./raytracer [FILE].ini\n"
# define LOAD_ERR "Error while loading scene file.\n"
# define ALLOC_ERR "Memory allocation error.\n"
# define SCE_WIDTH 1280
# define SCE_HEIGHT 1024
# define RAD(x) ((x) * M_PI / 180)
# define DEG(x) ((x) * 180 / M_PI)

#include "lapin.h"

typedef struct		s_vector
{
  double		x;
  double		y;
  double		z;
}			t_vector;

typedef struct			s_formes
{
  char				*name;
  char				*type;
  t_vector			pos;
  t_vector			rot;
  double			radius;
  t_bunny_accurate_position	size;
  double			intensity;
  t_color			color;
  char				found;
  double			ray_length;
  struct s_formes		*next;
}				t_formes;

typedef struct		s_math
{
  double		cos[360];
  double		sin[360];
  double		rotx[3][3];
  double		roty[3][3];
  double		rotz[3][3];
  t_bunny_position	screen_info[2];
  t_vector		origin;
  t_vector		ray;
  t_vector		simpleori;
  t_vector		simpleray;
}			t_math;

typedef struct		s_raytracer
{
  t_math		math;
  t_bunny_pixelarray	*scene;
  t_bunny_window	*win;
  t_formes		*formes;
  t_color		background;
}			t_raytracer;

/*
** math.c
*/

void	init_cos_sin(t_math *math);
void	init_matrices(t_math *math);
void	set_rotx(t_math *math, int teta);
void	set_roty(t_math *math, int teta);
void	set_rotz(t_math *math, int teta);

/*
** tcore
*/

void	tekpixel(t_bunny_pixelarray	*pix,
		 t_bunny_position	*pos,
		 t_color		*color);
void	tekray(const t_bunny_position	*screen_info,
	       int			*x,
	       int			*y,
	       int			*z);

/*
** display_formes.c
*/

t_formes	*closest_forme(t_formes *formes);
void		rtdisp(t_bunny_pixelarray *scene,
		       t_bunny_position *pixel,
		       t_formes *formes);

/*
** Miscs
*/

int	my_strlen(char *str);
int	my_getnbr(const char *str);
double	my_getdouble(const char *str);
char	*my_strdup(const char *str);
void	*tekfunction(const char *funcname);

/*
** Main Program : raytracer.c
*/

void	tekrayd(const t_bunny_position *screen_info,
		double *x, double *y, double *z);
int	raytracer(const char *scene);
void	aff_scene(t_raytracer *rayt);

/*
** Ini Loading : rtload.c
*/

t_bunny_pixelarray	*init_pix(t_bunny_ini_scope *scope,
				  const char *field);
void			init_pngs(t_formes *objects,
				 t_bunny_ini_scope *scope);
void			init_object(t_formes *obj,
				    t_bunny_ini *ini,
				    t_bunny_ini_scope *scope);
void			add_ptr_last(t_formes *object,
				     t_formes *last);
t_formes		*rtload(const char *file);
/*
** Display : src/rtdisplay.c
*/

void			calcs(t_raytracer *raytracer);
void			rtcalc(t_raytracer *raytracer,
			       t_formes *formes);
void			background(t_bunny_pixelarray *scene,
				   unsigned int color);
t_bunny_response	rayt_loop(void *data);

/*
** Keyboard : src/keyboard.c
*/

t_bunny_response	my_key(t_bunny_event_state state,
			       t_bunny_keysym keysym,
			       void *data);

/*
** Errors : src/error.c
*/

void	*my_puterror_null(const char *str);
int	my_puterror(const char *str, int error);

#endif /* !RAYTRACER_H_ */
