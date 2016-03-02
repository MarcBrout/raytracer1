/*
** tekpixel.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:25:37 2016 marc brout
** Last update Fri Feb 26 12:14:54 2016 marc brout
*/

#include "lapin.h"

void		tekpixel(t_bunny_pixelarray *pix,
			 t_bunny_position *pos,
			 t_color *color)
{
  t_color	*col;

  if ((pos->x >= 0) && (pos->x <= pix->clipable.clip_width) &&
      (pos->y >= 0) && (pos->y <= pix->clipable.clip_height))
    {
      col = (t_color*)pix->pixels +
	(pos->x + (pos->y * pix->clipable.clip_width));
      col->full = color->full;
    }
}
