/*
** tekray.c for rt
**
** Made by
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 10:40:46 2016
** Last update Thu Feb 25 11:19:57 2016 
*/

#include "lapin.h"

void		tekray(const t_bunny_position	*screen_info,
		       int			*x,
		       int			*y,
		       int			*z)
{
  *x = -(screen_info[0].x / 2) + screen_info[1].x;
  *y = -(screen_info[0].y / 2) + screen_info[1].y;
  *z = 100;
}
