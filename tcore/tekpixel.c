/*
** tekpixel.c for rt in
**
** Made by
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 10:38:19 2016
** Last update Thu Feb 25 10:39:36 2016 
*/

#include "lapin.h"

void		tekpixel(t_bunny_pixelarray	*pix,
			 t_bunny_position	*pos,
			 t_color		*color)
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
