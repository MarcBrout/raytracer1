/*
** ombres.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Sat Mar 12 15:25:21 2016 marc brout
** Last update Sat Mar 12 15:29:11 2016 marc brout
*/

#include <math.h>
#include "raytracer.h"

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

void		sub_shadow(t_raytracer *rt, t_formes *fo, t_formes *tmp2, t_formes *tmp)
{
  void		(*func)(t_formes *, t_vector *, t_vector *, int);

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
}

void		calc_ombre(t_raytracer *rt, t_formes *fo)
{
  t_formes	*tmp;
  t_formes	*tmp2;

  tmp = rt->spots;
  calc_new_simpleori(&rt->math.origin, &rt->math.ray,
		     fo->ray_length[0], &fo->realori);
  while ((tmp = tmp->next))
    {
      tmp2 = rt->formes;
      sub_vector(&fo->realray, &tmp->pos, &fo->realori);
      while ((tmp2 = tmp2->next))
	  sub_shadow(rt, fo, tmp2, tmp);
      tmp->found[2] = (check_ombre(rt->formes, fo)) ? 1 : 0;
    }
}
