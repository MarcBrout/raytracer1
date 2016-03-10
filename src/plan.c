/*
1;2802;0c** plan.c for raytracer
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Tue Mar  8 15:33:29 2016 marc brout
** Last update Thu Mar 10 22:46:13 2016 marc brout
*/

#include <stdio.h>
#include "raytracer.h"

void	plan(t_formes *plan,
	     t_vector *vec,
	     UNUSED t_vector *origin, int i)
{
  if (!vec->y)
    plan->found[i] = 0;
  else
    {
      plan->ray_length[i] = -(plan->size.x) / vec->y;
      if ((plan->ray_length[i]) >= 0)
	plan->found[i] = 1;
      else
	plan->found[i] = 0;
    }
}
