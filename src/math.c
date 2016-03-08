/*
** math.c for raytracer in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Tue Mar  8 19:28:31 2016 marc brout
** Last update Tue Mar  8 21:22:14 2016 marc brout
*/

#include <math.h>
#include "raytracer.h"

void		init_cos_sin(t_math *math)
{
  int		i;

  i = 0;
  while (i < 360)
    {
      math->cos[i] = cos(RAD((double)i));
      math->sin[i] = sin(RAD((double)i));
      i += 1;
    }
}

void		init_matrices(t_math *math)
{
  int		i;
  int		j;

  j = 0;
  while (j < 3)
    {
      i = 0;
      while (i < 3)
	{
	  math->rotx[j][i] = 0;
	  math->roty[j][i] = 0;
	  math->rotz[j][i] = 0;
	  i += 1;
	}
      j += 1;
    }
  math->rotx[1][1] = 1;
  math->roty[2][2] = 1;
  math->rotz[0][0] = 1;
}

void		set_rotx(t_math *math, int teta)
{
  math->rotx[0][0] = math->cos[teta];
  math->rotx[0][2] = math->sin[teta];
  math->rotx[2][0] = -math->sin[teta];
  math->rotx[2][2] = math->cos[teta];
}

void		set_roty(t_math *math, int teta)
{
  math->roty[0][0] = math->cos[teta];
  math->roty[0][1] = -math->sin[teta];
  math->roty[1][0] = math->sin[teta];
  math->roty[1][1] = math->cos[teta];
}

void		set_rotz(t_math *math, int teta)
{
  math->rotz[1][1] = math->cos[teta];
  math->rotz[1][2] = -math->sin[teta];
  math->rotz[2][1] = math->sin[teta];
  math->rotz[2][2] = math->cos[teta];
}
