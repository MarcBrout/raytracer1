/*
** rtload.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:24:55 2016 marc brout
** Last update Tue Mar  8 22:03:48 2016 marc brout
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "raytracer.h"

t_bunny_pixelarray		*init_pix(t_bunny_ini_scope *scope,
					  const char *field)
{
  int			fd;
  t_bunny_pixelarray	*tmp;
  const char		*str;

  if ((str = GET_F(scope, field, 0)))
    {
      if ((fd = open(str, O_RDWR) > 0))
  	{
	  tmp = bunny_load_pixelarray(str);
	  return (tmp);
  	}
    }
  return (NULL);
}

void			init_pngs(t_formes *object,
				  t_bunny_ini_scope *scope)
{
  (void)object;
  (void)scope;
}

void			init_object(t_formes *obj,
				    t_bunny_ini *ini,
				    t_bunny_ini_scope *scope)
{
  obj->name = my_strdup(bunny_ini_scope_name(ini, scope));
  obj->type = my_strdup(GET_F(scope, "type", 0));
  obj->pos.x = my_getdouble((char *)(GET_F(scope, "pos", 0)));
  obj->pos.y = my_getdouble((char *)(GET_F(scope, "pos", 1)));
  obj->pos.z = my_getdouble((char *)(GET_F(scope, "pos", 2)));
  obj->rot.x = (int)my_getdouble((char *)(GET_F(scope, "rot", 0)));
  obj->rot.y = (int)my_getdouble((char *)(GET_F(scope, "rot", 1)));
  obj->rot.z = (int)my_getdouble((char *)(GET_F(scope, "rot", 2)));
  obj->rot.x = (((int)obj->rot.x % 360) + 360) % 360;
  obj->rot.y = (((int)obj->rot.y % 360) + 360) % 360;
  obj->rot.z = (((int)obj->rot.z % 360) + 360) % 360;
  obj->radius = my_getdouble((char *)(GET_F(scope, "radius", 0)));
  obj->size.x = my_getdouble((char *)(GET_F(scope, "height", 0)));
  obj->size.y = my_getdouble((char *)(GET_F(scope, "width", 0)));
  obj->intensity = my_getdouble((char *)(GET_F(scope, "intensity", 0)));
  obj->color.argb[3] = my_getnbr((char *)(GET_F(scope, "color", 0)));
  obj->color.argb[0] = my_getnbr((char *)(GET_F(scope, "color", 1)));
  obj->color.argb[1] = my_getnbr((char *)(GET_F(scope, "color", 2)));
  obj->color.argb[2] = my_getnbr((char *)(GET_F(scope, "color", 3)));
  obj->next = NULL;
}

void			add_ptr_last(t_formes *object, t_formes *last)
{
  t_formes		*tmp;

  tmp = object;
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = last;
}

t_formes		*rtload(const char *file)
{
  t_bunny_ini		*ini;
  t_bunny_ini_scope	*scope;
  t_formes		*objects;
  t_formes		*tmp;

  if (!(ini = bunny_load_ini(file)) || !(scope = bunny_ini_first(ini)))
    return (my_puterror_null(NO_FILE));
  if (!(objects = bunny_malloc(sizeof(t_formes))))
    return (my_puterror_null(ALLOC_ERR));
  objects->next = NULL;
  init_object(objects, ini, scope);
  while ((scope = bunny_ini_next(ini, scope)) != LAST_SCOPE)
    {
      if (!(tmp = bunny_malloc(sizeof(t_formes))))
	return (my_puterror_null(ALLOC_ERR));
      init_object(tmp, ini, scope);
      add_ptr_last(objects, tmp);
      tmp = tmp->next;
    }
  bunny_delete_ini(ini);
  return (objects);
}
