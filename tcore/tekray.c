/*
** tekray.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:25:48 2016 marc brout
** Last update Fri Feb 26 12:15:16 2016 marc brout
*/

#include "lapin.h"

void		tekray(const t_bunny_position *screen_info,
		       int *x,
		       int *y,
		       int *z)
{
  *x = -(screen_info[0].x / 2) + screen_info[1].x;
  *y = -(screen_info[0].y / 2) + screen_info[1].y;
  *z = 100;
}
