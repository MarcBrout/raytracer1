/*
** free.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1/src
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Sat Mar 12 17:29:56 2016 marc brout
** Last update Sat Mar 12 17:38:42 2016 marc brout
*/

#include <stdlib.h>
#include "raytracer.h"

void		free_list(t_formes *formes)
{
  t_formes	*tmp;
  t_formes	*tmp2;

  tmp = formes->next;
  while (tmp->next)
    {
      tmp2 = tmp->next;
      free(tmp->name);
      free(tmp);
      tmp = tmp2;
    }
  free(formes);
}
