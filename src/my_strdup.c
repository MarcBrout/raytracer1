/*
** my_strdup.c for my_strdup in /home/brout_m/dev/piscine/PJ8
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Wed Oct  7 10:24:46 2015 marc brout
** Last update Thu Feb 25 16:23:36 2016 marc brout
*/

#include <stdlib.h>
#include "raytracer.h"x

char	*my_strdup(const char *src)
{
  int	i;
  char	*dest;

  i = 0;
  dest = NULL;
  if (src)
    {
      if ((dest = malloc(sizeof(char) * my_strlen((char *)src) + 1)) == NULL)
	return (NULL);
      while (src[i])
	{
	  dest[i] = src[i];
	  i = i + 1;
	}
      dest[i] = 0;
    }
  return (dest);
}
