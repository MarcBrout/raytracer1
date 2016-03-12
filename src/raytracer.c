/*
** raytracer.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:24:25 2016 marc brout
** Last update Sat Mar 12 17:35:46 2016 marc brout
*/

#include <unistd.h>
#include "raytracer.h"

void		tekrayd(const t_bunny_position *screen_info,
		       double *x, double *y, double *z)
{
  *x = -(screen_info[0].x / 2) + screen_info[1].x;
  *y = (screen_info[0].y / 2) - screen_info[1].y;
  *z = 500;
}

void		aff_scene(t_raytracer *rayt)
{
  bunny_set_key_response(my_key);
  /* bunny_set_loop_main_function(rayt_loop); */
  /* bunny_loop(rayt->win, 25, rayt); */  bunny_delete_clipable(&rayt->scene->clipable);
  bunny_stop(rayt->win);
}

int		count_forme(t_formes *formes)
{
  t_formes	*tmp;
  int		i;

  tmp = formes;
  i = 0;
  while ((tmp = tmp->next))
    i += 1;
  return (i);
}

int		raytracer(const char *scene)
{
  t_raytracer	rayt;

  if (!(rayt.formes = rtload(scene)) ||
      !(rayt.spots = rtload_spots(scene)))
    return (my_puterror(LOAD_ERR, 1));
  rayt.nbspot = count_forme(rayt.spots);
  init_functab(&rayt);
  if (!(rayt.scene = bunny_new_pixelarray(SCE_WIDTH, SCE_HEIGHT)) ||
      !(rayt.win = bunny_start(SCE_WIDTH, SCE_HEIGHT, 0, "Raytracer1")))
    return (my_puterror(ALLOC_ERR, 1));
  init_cos_sin(&rayt.math);
  init_matrices(&rayt.math);
  aff_scene(&rayt);
  free_list(rayt.formes);
  free_list(rayt.spots);
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
