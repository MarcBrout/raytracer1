/*
** display_formes.c for raytracer
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Wed Mar  2 17:16:23 2016 marc brout
** Last update Wed Mar  2 19:17:05 2016 marc brout
*/

#include "raytracer.h"


t_formes	*closest_forme(t_formes *formes)
{
  t_formes	*tmp;
  t_formes	*smallest;

  tmp = formes->next;
  smallest = NULL;
  while (tmp)
    {
      if (!smallest && tmp->found && tmp->ray_length >= 0)
	smallest = tmp;
      else if (smallest && tmp->found &&
	       tmp->ray_length < smallest->ray_length
	       && tmp->ray_length > 0)
	smallest = tmp;
      tmp = tmp->next;
    }
  return (smallest);
}

void		rtdisp(t_bunny_pixelarray *scene,
		       t_bunny_position *pixel,
		       t_formes *formes)
{
  t_formes	*tmp;
  unsigned int	*pixels;

  pixels = scene->pixels;
  if (!(tmp = closest_forme(formes)))
    return ;
  pixels[pixel->x + pixel->y * scene->clipable.clip_width] =
    tmp->color.full;
}
