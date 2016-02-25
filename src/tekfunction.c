/*
** tekfunction.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:25:15 2016 marc brout
** Last update Thu Feb 25 16:25:17 2016 marc brout
*/

#include <stdlib.h>
#include <dlfcn.h>

void		*tekfunction(const char *funcname)
{
  void		*handle;

  if (!(handle = dlopen(NULL, RTLD_LAZY)))
    return (NULL);
  dlerror();
  return (dlsym(handle, funcname));
}
