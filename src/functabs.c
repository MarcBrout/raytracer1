/*
** functabs.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1/src
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Sat Mar 12 16:29:23 2016 marc brout
** Last update Sat Mar 12 16:39:46 2016 marc brout
*/

#include "raytracer.h"

void	init_functab(t_raytracer *rt)
{
  rt->tabinter[0] = &sphere;
  rt->tabinter[1] = &plan;
  rt->tabomb[0] = &spotsphere;
  rt->tabomb[1] = &spotplan;
}
