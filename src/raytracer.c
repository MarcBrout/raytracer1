/*
** raytracer.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:24:25 2016 marc brout
** Last update Wed Mar  2 18:27:57 2016 marc brout
*/

#include <stdio.h>
#include <unistd.h>
#include "raytracer.h"

void		tekrayd(const t_bunny_position *screen_info,
		       double *x, double *y, double *z)
{
  *x = -(screen_info[0].x / 2) + screen_info[1].x;
  *y = -(screen_info[0].y / 2) + screen_info[1].y;
  *z = 100;
}

void		aff_scene(t_raytracer *rayt)
{
  bunny_set_key_response(my_key);
  bunny_set_loop_main_function(rayt_loop);
  bunny_loop(rayt->win, 25, rayt);
  bunny_delete_clipable(&rayt->scene->clipable);
  bunny_stop(rayt->win);
}

void		debug(t_formes *formes)
{
  t_formes	*tmp;

  tmp = formes->next;
  while (tmp)
    {
      printf("name = %s\n", tmp->name);
      printf("type = %s\n", tmp->type);
      printf("pos : x = %f, y = %f, z = %f\n", tmp->pos.x,
	     tmp->pos.y, tmp->pos.z);
      printf("radius = %f\n", tmp->radius);
      printf("intensity = %f\n\n", tmp->intensity);
      tmp = tmp->next;
    }
}

int		raytracer(const char *scene)
{
  t_raytracer	rayt;

  if (!(rayt.formes = rtload(scene)))
    return (my_puterror(LOAD_ERR, 1));
  if (!(rayt.scene = bunny_new_pixelarray(SCE_WIDTH, SCE_HEIGHT)) ||
      !(rayt.win = bunny_start(SCE_WIDTH, SCE_HEIGHT, 0, "Raytracer1")))
    return (my_puterror(ALLOC_ERR, 1));
  debug(rayt.formes);
  aff_scene(&rayt);
  return (0);
}

int		main(int ac, char **av)
{
  if (ac < 2)
    return (my_puterror(USAGE, 1));
  if (raytracer(av[1]))
    return (1);
  return (0);
}
