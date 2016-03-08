/*
** plan.c for raytracer in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Tue Mar  8 15:33:29 2016 marc brout
** Last update Tue Mar  8 19:27:09 2016 marc brout
*/

#include <stdio.h>
#include "raytracer.h"

void	plan(t_formes *plan,
	     t_vector *vec,
	     UNUSED t_vector *origin)
{
  if (!vec->y)
    plan->found = 0;
  else
    {
      plan->ray_length = -(plan->size.x) / vec->y;
      if ((plan->ray_length) >= 0)
	plan->found = 1;
      else
	plan->found = 0;
    }
}
