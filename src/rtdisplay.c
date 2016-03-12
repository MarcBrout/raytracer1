/*
** rtdisplay.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:24:38 2016 marc brout
** Last update Sat Mar 12 15:34:21 2016 marc brout
*/

#include <math.h>
#include "raytracer.h"

void			calcs(t_raytracer *rayt)
{
  rayt->math.screen_info[0].x = rayt->scene->clipable.clip_width;
  rayt->math.screen_info[0].y = rayt->scene->clipable.clip_height;
  rayt->math.screen_info[1].y = 0;
  rayt->math.origin.z = 0;
  rayt->math.origin.y = 0;
  rayt->math.origin.x = 0;
  while (rayt->math.screen_info[1].y < rayt->math.screen_info[0].y)
    {
      rayt->math.screen_info[1].x = 0;
      while (rayt->math.screen_info[1].x < rayt->math.screen_info[0].x)
	{
	      tekrayd(rayt->math.screen_info, &rayt->math.ray.x,
		      &rayt->math.ray.y, &rayt->math.ray.z);
	      rtcalc(rayt, rayt->formes);
	      rtdisp(rayt, rayt->scene, &rayt->math.screen_info[1], rayt->formes);
	      rayt->math.screen_info[1].x += 1;
	}
      rayt->math.screen_info[1].y += 1;
    }
}

void		calc_cos(t_formes *forme,
			 t_formes *spot)
{
  double	norme_ray;
  double	norme_normal;
  double	scalaire;

  norme_ray = sqrt(spot->lightray.x * spot->lightray.x +
		   spot->lightray.y * spot->lightray.y +
		   spot->lightray.z * spot->lightray.z);
  norme_normal = sqrt(forme->normal.x * forme->normal.x +
		      forme->normal.y * forme->normal.y +
		      forme->normal.z * forme->normal.z);
  scalaire = (spot->lightray.x * forme->normal.x +
	      spot->lightray.y * forme->normal.y +
	      spot->lightray.z * forme->normal.z);
  spot->cos = scalaire / (norme_ray * norme_normal);
}

void		rtcalc(t_raytracer *rt, t_formes *formes)
{
  t_formes	*tmp;
  void		(*func)(t_formes *, t_vector *, t_vector *, int);

  tmp = formes;
  while ((tmp = tmp->next))
    {
      if (tmp->type &&
	  (func = (void (*)(t_formes *, t_vector  *, t_vector *, int))
	   tekfunction(tmp->type)))
	{
	  set_rotx(&rt->math, (360 - (int)tmp->rot.x) % 360);
	  set_roty(&rt->math, (360 - (int)tmp->rot.y) % 360);
	  set_rotz(&rt->math, (360 - (int)tmp->rot.z) % 360);
	  translate_cam(&tmp->pos, &rt->math.origin, &tmp->simpleori);
	  simple_position(&tmp->simpleori, &tmp->simpleori, &rt->math);
	  simple_position(&rt->math.ray, &tmp->simpleray, &rt->math);
	  func(tmp, &tmp->simpleray, &tmp->simpleori, 0);
	}
    }
}

void			background(t_bunny_pixelarray *scene,
				   unsigned int color)
{
  unsigned int		*pix;
  int			total;
  int			i;

  i = 0;
  pix = (unsigned int *)scene->pixels;
  total = scene->clipable.clip_width * scene->clipable.clip_height;
  while (i < total)
    {
      pix[i] = color;
      i = i + 1;
    }
}

t_bunny_response	rayt_loop(void *data)
{
  t_raytracer		*rayt;

  rayt = (t_raytracer *)data;
  background(rayt->scene, rayt->formes->color.full);
  calcs(rayt);
  bunny_blit(&rayt->win->buffer, &rayt->scene->clipable, NULL);
  bunny_display(rayt->win);
  return (GO_ON);
}
