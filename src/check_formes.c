/*
** check_formes.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Sat Mar 12 15:24:02 2016 marc brout
** Last update Sat Mar 12 15:24:37 2016 marc brout
*/

#include "raytracer.h"

t_formes	*closest_forme(t_formes *formes)
{
  t_formes	*tmp;
  t_formes	*smallest;

  tmp = formes->next;
  smallest = NULL;
  while (tmp)
    {
      if (!smallest && tmp->found[0] && tmp->ray_length[0] >= 0)
	smallest = tmp;
      else if (smallest && tmp->found[0] &&
	       tmp->ray_length[0] < smallest->ray_length[0]
	       && tmp->ray_length[0] > 0)
	smallest = tmp;
      tmp = tmp->next;
    }
  return (smallest);
}

double		check_ombre(t_formes *formes, t_formes *cur)
{
  t_formes	*tmp;

  tmp = formes;
  while ((tmp = tmp->next))
    {
      if (tmp->found[1] && tmp != cur)
	{
	  if (tmp->ray_length[1] > 0 && tmp->ray_length[1] < 1)
	    return (1);
	}
    }
  return (0);
}

t_formes 	*biggest_cos(t_formes *spots)
{
  t_formes	*tmp;
  t_formes	*maxcos;

  tmp = spots;
  maxcos = NULL;
  while ((tmp = tmp->next))
    {
      if (!maxcos && tmp)
	maxcos = tmp;
      else if (maxcos && tmp && maxcos->cos < tmp->cos)
	maxcos = tmp;
    }
  return (maxcos);
}
