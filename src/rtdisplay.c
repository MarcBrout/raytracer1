/*
** rtdisplay.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
n**
** Started on  Thu Feb 25 16:24:38 2016 marc brout
** Last update Fri Mar 11 00:22:10 2016 marc brout
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
	  /* if (rayt->math.screen_info[1].x == rayt->math.screen_info[0].x / 2 && rayt->math.screen_info[1].y == rayt->math.screen_info[0].y / 2) */
	  /*   { */
	      tekrayd(rayt->math.screen_info, &rayt->math.ray.x,
		      &rayt->math.ray.y, &rayt->math.ray.z);
	      rtcalc(rayt, rayt->formes);
	      rtdisp(rayt, rayt->scene, &rayt->math.screen_info[1], rayt->formes);
	    /* } */
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

void		calc_ombre(t_raytracer *rt, t_formes *forme)
{
  t_formes	*tmp;
  t_formes	*tmp2;
  void		(*func)(t_formes *, t_vector *, t_vector *, int);
  t_vector	realori;
  t_vector	realray;
  t_vector	simpleori;
  t_vector	simpleray;

  tmp = rt->spots;
  calc_new_simpleori(&rt->math.origin, &rt->math.ray,
		     forme->ray_length[0], &realori);
  /* printf("%s\n", forme->name); */
  /* printf("K= %f\n", forme->ray_length[0]); */
  /* printf("realori : x=%f, y=%f, z=%f\n", realori.x, realori.y,realori.z); */
  /* printf("tekray : x=%f, y=%f, z=%f\n", rt->math.ray.x, rt->math.ray.y,rt->math.ray.z); */
  while ((tmp = tmp->next))
    {
      tmp2 = rt->formes;
      sub_vector(&realray, &tmp->pos, &realori);
      while ((tmp2 = tmp2->next))
	if (tmp2->type &&
	    (func = (void (*)(t_formes *, t_vector  *, t_vector *, int))
	     tekfunction(tmp2->type)))
	  {
	    set_rotx(&rt->math, (360 - (int)tmp2->rot.x) % 360);
	    set_roty(&rt->math, (360 - (int)tmp2->rot.y) % 360);
	    set_rotz(&rt->math, (360 - (int)tmp2->rot.z) % 360);
	    /* printf("spotpos : x=%f, y=%f, z=%f\n", tmp->pos.x, tmp->pos.y,tmp->pos.z); */
	    /* printf("realray : x=%f, y=%f, z=%f\n", realray.x, realray.y,realray.z); */
	    sub_vector(&simpleori, &realori, &tmp2->pos);
	    simple_position(&simpleori, &simpleori, &rt->math);
	    simple_position(&realray, &simpleray, &rt->math);
	    /* printf("simpleori : x=%f, y=%f, z=%f\n", simpleori.x, simpleori.y,simpleori.z); */
	    /* printf("simpleray : x=%f, y=%f, z=%f\n", simpleray.x, simpleray.y,simpleray.z); */
	    func(tmp2, &simpleray, &simpleori, 1);
	    /* printf("found = %d, %f\n", tmp2->found[1], */
	    /* 	   tmp2->ray_length[1]); */
	  }
	else if (tmp2 == forme)
	  forme->found[1] = 0;
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
	  /* printf("inter oldori : x=%f, y=%f, z=%f\n", tmp->simpleori.x, tmp->simpleori.y, tmp->simpleori.z); */

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
