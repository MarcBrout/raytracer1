/*
** display_formes.c for raytracer
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Wed Mar  2 17:16:23 2016 marc brout
** Last update Fri Mar 11 00:47:46 2016 marc brout
*/

#include "raytracer.h"
#include <stdio.h>

t_formes	*closest_forme(t_formes *formes)
{
  t_formes	*tmp;
  t_formes	*smallest;

  tmp = formes->next;
  smallest = NULL;
  while (tmp)
    {
      if (!smallest && tmp->found[0] && tmp->ray_length[0] >= 0)
	smallest = tmp;
      else if (smallest && tmp->found[0] &&
	       tmp->ray_length[0] < smallest->ray_length[0]
	       && tmp->ray_length[0] > 0)
	smallest = tmp;
      tmp = tmp->next;
    }
  return (smallest);
}

double		check_ombre(t_formes *formes, t_formes *cur)
{
  t_formes	*tmp;

  tmp = formes;
  while ((tmp = tmp->next))
    {
      if (tmp != cur && tmp->found[1])
	{
	  if (tmp->ray_length[1] > 0 && tmp->ray_length[1] < 1)
	    return (1);
	}
    }
  return (0);
}

void		rtdisp(t_raytracer *raytracer,
		       t_bunny_pixelarray *scene,
		       t_bunny_position *pixel,
		       t_formes *formes)
{
  t_formes	*tmp;
  unsigned int	*pixels;

  pixels = scene->pixels;
  if (!(tmp = closest_forme(formes)))
    return ;
  calc_ombre(raytracer, tmp);
  if (!check_ombre(formes, tmp))
    pixels[pixel->x + pixel->y * scene->clipable.clip_width] =
      tmp->color.full;
}
