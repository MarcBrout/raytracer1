/*
** raytracer.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:24:25 2016 marc brout
** Last update Thu Feb 25 16:24:27 2016 marc brout
*/

#include <stdio.h>
#include <unistd.h>
#include "raytracer.h"

int	my_put_error(const char *str)
{
  write(2, str, my_strlen((char *)str));
  return (1);
}

int	main(int ac, char **av)
{
  double test;

  if (ac < 1)
    return (my_put_error(USAGE));
  test = my_getdouble(av[1]);
  printf("%f\n", test);
  return (0);
}
