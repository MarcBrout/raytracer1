/*
** error.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Fri Feb 26 14:30:26 2016 marc brout
** Last update Fri Feb 26 15:36:08 2016 marc brout
*/

#include <stdlib.h>
#include <unistd.h>
#include "raytracer.h"

int		my_puterror(const char *str, int error)
{
  write(2, str, my_strlen((char *)str));
  return (error);
}

void		*my_puterror_null(const char *str)
{
  write(2, str, my_strlen((char *)str));
  return (NULL);
}
