/*
** keyboad.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Fri Feb 26 12:10:28 2016 marc brout
** Last update Fri Feb 26 12:30:30 2016 marc brout
*/

#include "raytracer.h"

t_bunny_response	my_key(t_bunny_event_state state,
			       t_bunny_keysym keysym,
			       UNUSED void *data)
{
  if (keysym == BKS_ESCAPE && state == GO_DOWN)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}
