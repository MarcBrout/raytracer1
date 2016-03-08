/*
** sphere.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Wed Mar  2 16:20:46 2016 marc brout
** Last update Tue Mar  8 23:02:31 2016 marc brout
*/

#include <stdio.h>
#include <math.h>
#include "raytracer.h"

void		calc_abc(t_formes *sphere,
			 t_vector *vec,
			 t_vector *ori,
			 t_vector *abc)
{
  abc->x = vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
  abc->y = 2 * (vec->x * ori->x + vec->y * ori->y + vec->z * ori->z);
  abc->z = ((ori->x * ori->x + ori->y * ori->y + ori->z * ori->z)
	    - sphere->radius * sphere->radius);
}

double		calc_delta(t_vector *abc)
{
  double	delta;

  delta = (abc->y * abc->y) - (4 * abc->x * abc->z);
  return (delta);
}

double		calc_closest_intersection(t_vector *abc, double delta)
{
  double	len1;
  double	len2;

  len1 = (-abc->y + sqrt(delta)) / (2 * abc->x);
  len2 = (-abc->y - sqrt(delta)) / (2 * abc->x);
  if (len1 > len2)
    return (len2);
  return (len1);
}

void		sphere(t_formes *sphere,
		       t_vector *vec,
		       t_vector *origin)
{
  t_vector	abc;
  double	delta;

  calc_abc(sphere, vec, origin, &abc);
  if ((delta = calc_delta(&abc)) < 0)
    sphere->found = 0;
  else
    {
      sphere->found = 1;
      if (!delta)
	sphere->ray_length = -(abc.y / (2 * abc.x));
      else
	sphere->ray_length = calc_closest_intersection(&abc, delta);
    }
}
