/*
** display_formes.c for raytracer
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Wed Mar  2 17:16:23 2016 marc brout
** Last update Fri Mar 18 01:55:38 2016 marc brout
*/

#include "raytracer.h"

void		apply_color(t_bunny_pixelarray *scene,
			    t_bunny_position *pixel,
			    t_formes *forme,
			    t_formes *spot)
{
  t_color	*pixels;
  int		pos;

  pixels = scene->pixels;
  pos = pixel->x + pixel->y * scene->clipable.clip_width;
  pixels[pos].full = forme->color.full;
  spot->cos += 0.1;
  if (spot->cos > 1)
    spot->cos = 1;
  pixels[pos].argb[0] = forme->color.argb[0] * spot->cos;
  pixels[pos].argb[1] = forme->color.argb[1] * spot->cos;
  pixels[pos].argb[2] = forme->color.argb[2] * spot->cos;
}

int		check_spots(t_formes *spots)
{
  t_formes	*tmp;
  int		total;

  tmp = spots;
  total = 0;
  while ((tmp = tmp->next))
    {
      if (tmp->found[2])
	total += 1;
    }
  return (total);
}

void		rtdisp(t_raytracer *raytracer,
		       t_bunny_pixelarray *scene,
		       t_bunny_position *pixel,
		       t_formes *formes)
{
  t_formes	*close_fo;
  t_formes	*big_cos;
  int		nb;

  if (!(close_fo = closest_forme(formes)))
    return ;
  calc_ombre(raytracer, close_fo);
  calc_luminosity(raytracer, close_fo);
  if (!(big_cos = biggest_cos(raytracer->spots)))
    return ;
  nb = check_spots(raytracer->spots);
  if (nb)
    big_cos->cos = big_cos->cos / (nb + 1);
  if (big_cos->cos < 0)
    big_cos->cos = 0;
  apply_color(scene, pixel, close_fo, big_cos);
}
