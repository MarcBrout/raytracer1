/*
** rtdisplay.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:24:38 2016 marc brout
** Last update Fri Mar 11 21:00:37 2016 marc brout
*/

#include <stdio.h>
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

void		translate_cam(t_vector *forme,
			      t_vector *origin,
			      t_vector *output)
{
  output->x = origin->x - forme->x;
  output->y = origin->y - forme->y;
  output->z = origin->z - forme->z;
}

void		calc_new_simpleori(t_vector *simpleori,
				   t_vector *simpleray,
				   double len,
				   t_vector *output)
{
  output->x = simpleori->x + simpleray->x * len;
  output->y = simpleori->y + simpleray->y * len;
  output->z = simpleori->z + simpleray->z * len;
}

void		sub_vector(t_vector *output,
			   t_vector *one,
			   t_vector *two)
{
  output->x = one->x - two->x;
  output->y = one->y - two->y;
  output->z = one->z - two->z;
}

void		spotplan(t_formes *forme,
			 UNUSED t_formes *spot,
			 t_math *math)
{
  t_vector	tmp;

  tmp.x = 0;
  tmp.y = 500;
  tmp.z = 0;
  simple_position(&tmp, &forme->normal, math);
}

void		spotsphere(t_formes *forme,
			   UNUSED t_formes *spot,
			   t_math *math)
{
  simple_position(&forme->simpleori, &forme->normal, math);
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
  /* printf("%f\n", spot->cos); */
}

void		calc_luminosity(t_raytracer *rt, t_formes *fo)
{
  t_formes	*tmp;
  void		(*func)(t_formes *, t_formes *, t_math *);

  tmp = rt->spots;
  set_rotx(&rt->math, (int)fo->rot.x);
  set_roty(&rt->math, (int)fo->rot.y);
  set_rotz(&rt->math, (int)fo->rot.z);
  if (fo->spot && (func = (void (*)(t_formes *, t_formes *, t_math *))
		   tekfunction(fo->spot)))
    func(fo, tmp, &rt->math);
  while ((tmp = tmp->next))
    calc_cos(fo, tmp);
}


void		calc_ombre(t_raytracer *rt, t_formes *fo)
{

  t_formes	*tmp;
  t_formes	*tmp2;
  void		(*func)(t_formes *, t_vector *, t_vector *, int);

  tmp = rt->spots;
  calc_new_simpleori(&rt->math.origin, &rt->math.ray,
		     fo->ray_length[0], &fo->realori);
  while ((tmp = tmp->next))
    {
      tmp2 = rt->formes;
      sub_vector(&fo->realray, &tmp->pos, &fo->realori);
      while ((tmp2 = tmp2->next))
	if (tmp2->type && (func = (void (*)(t_formes *, t_vector  *, t_vector *, int))
			   tekfunction(tmp2->type)))
	  {
	    set_rotx(&rt->math, (360 - (int)tmp2->rot.x) % 360);
	    set_roty(&rt->math, (360 - (int)tmp2->rot.y) % 360);
	    set_rotz(&rt->math, (360 - (int)tmp2->rot.z) % 360);
	    sub_vector(&tmp2->simpleori, &fo->realori, &tmp2->pos);
	    simple_position(&tmp2->simpleori, &tmp2->simpleori, &rt->math);
	    simple_position(&fo->realray, &tmp2->simpleray, &rt->math);
	    func(tmp2, &tmp2->simpleray, &tmp2->simpleori, 1);
	    if (tmp2 == fo)
	      {
		tmp->lightray.x = tmp2->simpleray.x;
		tmp->lightray.y = tmp2->simpleray.y;
		tmp->lightray.z = tmp2->simpleray.z;
	      }
	  }
      tmp->found[2] = (check_ombre(rt->formes, fo)) ? 1 : 0;
    }
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
