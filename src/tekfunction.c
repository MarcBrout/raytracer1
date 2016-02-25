/*
** tekfunction.c for rt
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Mon Feb 15 11:06:53 2016 marc brout
** Last update Thu Feb 25 16:00:39 2016 marc brout
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
