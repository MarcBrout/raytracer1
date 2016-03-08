/*
** rtdisplay.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:24:38 2016 marc brout
** Last update Wed Mar  9 00:09:05 2016 marc brout
*/

#include <stdio.h>
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
	  rtdisp(rayt->scene, &rayt->math.screen_info[1], rayt->formes);
	  rayt->math.screen_info[1].x += 1;
	}
      rayt->math.screen_info[1].y += 1;
    }
}

void		multiply_by_mat(t_vector *result, t_vector *calc, double rot[3][3])
{
  result->z = calc->z * rot[0][0] + calc->x * rot[0][1] + calc->y * rot[0][2];
  result->x = calc->z * rot[1][0] + calc->x * rot[1][1] + calc->y * rot[1][2];
  result->y = calc->z * rot[2][0] + calc->x * rot[2][1] + calc->y * rot[2][2];
}

void		simple_position(t_vector *input, t_vector *output, t_math *math)
{
  t_vector	tmp;

  tmp.x = input->x;
  tmp.y = input->y;
  tmp.z = input->z;
  multiply_by_mat(output, &tmp, math->rotx);
  tmp.x = output->x;
  tmp.y = output->y;
  tmp.z = output->z;
  multiply_by_mat(output, &tmp, math->roty);
  tmp.x = output->x;
  tmp.y = output->y;
  tmp.z = output->z;
  multiply_by_mat(output, &tmp, math->rotz);
}

void		translate_cam(t_formes *forme, t_math *math, t_vector *output)
{
  output->x = math->origin.x - forme->pos.x;
  output->y = math->origin.y - forme->pos.y;
  output->z = math->origin.z - forme->pos.z;
}

void		rtcalc(t_raytracer *rt, t_formes *formes)
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
	{
	  set_rotx(&rt->math, (360 - (int)tmp->rot.x) % 360);
	  set_roty(&rt->math, (360 - (int)tmp->rot.y) % 360);
	  set_rotz(&rt->math, (360 - (int)tmp->rot.z) % 360);
	  translate_cam(tmp, &rt->math, &rt->math.simpleori);
	  simple_position(&rt->math.simpleori,
			  &rt->math.simpleori, &rt->math);
	  simple_position(&rt->math.ray,
			  &rt->math.simpleray, &rt->math);
	  func(tmp, &rt->math.simpleray, &rt->math.simpleori);
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
