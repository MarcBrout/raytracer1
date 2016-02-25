/*
** raytracer.h for rt
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:26:01 2016 marc brout
** Last update Thu Feb 25 16:26:09 2016 marc brout
*/

#ifndef RAYTRACER_H_
# define RAYTRACER_H_
# define USAGE "Usage: ./raytracer [FILE].ini\n"
# define GET_F bunny_ini_scope_get_field

#include "lapin.h"

typedef struct		s_raytracer
{
  t_bunny_pixelarray	*scene;
  t_bunny_window	*win;
}			t_raytracer;

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
  t_vector			origin;
  double			radius;
  t_bunny_accurate_position	size;
  double			intensity;
  t_color			color;
  struct s_formes		*next;
}				t_formes;

void	tekpixel(t_bunny_pixelarray	*pix,
		 t_bunny_position	*pos,
		 t_color		*color);
void	tekray(const t_bunny_position	*screen_info,
	       int			*x,
	       int			*y,
	       int			*z);
int	my_strlen(char *str);
int	my_getnbr(const char *str);
double	my_getdouble(const char *str);
char	*my_strdup(const char *str);
void	*tekfunction(const char *funcname);

#endif
