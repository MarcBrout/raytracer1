/*
** rtdisplay.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:24:38 2016 marc brout
** Last update Wed Mar  2 18:03:31 2016 marc brout
*/

#include <stdio.h>
#include "raytracer.h"

void			calcs(t_raytracer *raytracer)
{
  t_bunny_position	screen_info[2];
  t_vector		rayvector;
  t_vector		origin;

  origin.x = 0;
  origin.y = 0;
  origin.z = 0;
  screen_info[0].x = raytracer->scene->clipable.clip_width;
  screen_info[0].y = raytracer->scene->clipable.clip_height;
  screen_info[1].y = 0;
  while (screen_info[1].y < screen_info[0].y)
    {
      screen_info[1].x = 0;
      while (screen_info[1].x < screen_info[0].x)
	{
	  tekrayd(screen_info, &rayvector.x, &rayvector.y, &rayvector.z);
	  rtcalc(raytracer->formes, &rayvector, &origin);
	  rtdisp(raytracer->scene, &screen_info[1], raytracer->formes);
	  screen_info[1].x += 1;
	}
      screen_info[1].y += 1;
    }
}

void		rtcalc(t_formes *formes,
		       t_vector *ray,
		       t_vector *origin)
{
  t_formes	*tmp;
  int		i;
  void		(*func)(t_formes *, t_vector *, t_vector *);

  tmp = formes;
  i = 0;
  while ((tmp = tmp->next))
    {
      i += 1;
      if (tmp->type &&
	  (func = (void (*)(t_formes *, t_vector  *, t_vector *))
	   tekfunction(tmp->type)))
	func(tmp, ray, origin);
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
