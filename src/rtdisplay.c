/*
** rtdisplay.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:24:38 2016 marc brout
** Last update Thu Feb 25 16:24:39 2016 marc brout
*/

#include <stdio.h>
#include "raytracer.h"

void		rtdisplay(t_bunny_pixelarray	*pix,
			  t_formes		*formes)
{
  t_formes	*tmp;
  int		i;
  void		(*func)(t_bunny_pixelarray *, t_formes *);

  tmp = formes;
  i = 0;
  while ((tmp = tmp->next))
    {
      i += 1;
      printf("test %d, %s\n", i, tmp->name);
      if (tmp->type &&
	  (func = (void (*)(t_bunny_pixelarray *, t_formes *))
	   tekfunction(tmp->type)))
	func(pix, tmp);
    }
}
