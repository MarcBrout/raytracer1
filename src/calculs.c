/*
** calculs.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Sat Mar 12 15:29:49 2016 marc brout
** Last update Sat Mar 12 15:30:42 2016 marc brout
*/

#include "raytracer.h"

void		multiply_by_mat(t_vector *result, t_vector *calc, double rot[3][3])
{
  result->z = calc->z * rot[0][0] + calc->x * rot[0][1] + calc->y * rot[0][2];
  result->x = calc->z * rot[1][0] + calc->x * rot[1][1] + calc->y * rot[1][2];
  result->y = calc->z * rot[2][0] + calc->x * rot[2][1] + calc->y * rot[2][2];
}

void		simple_position(t_vector *input, t_vector *output, t_math *math)
{
  t_vector	tmp;

  tmp.x = input->x;
  tmp.y = input->y;
  tmp.z = input->z;
  multiply_by_mat(output, &tmp, math->rotx);
  tmp.x = output->x;
  tmp.y = output->y;
  tmp.z = output->z;
  multiply_by_mat(output, &tmp, math->roty);
  tmp.x = output->x;
  tmp.y = output->y;
  tmp.z = output->z;
  multiply_by_mat(output, &tmp, math->rotz);
}

void		translate_cam(t_vector *forme,
			      t_vector *origin,
			      t_vector *output)
{
  output->x = origin->x - forme->x;
  output->y = origin->y - forme->y;
  output->z = origin->z - forme->z;
}

void		calc_new_simpleori(t_vector *simpleori,
				   t_vector *simpleray,
				   double len,
				   t_vector *output)
{
  output->x = simpleori->x + simpleray->x * len;
  output->y = simpleori->y + simpleray->y * len;
  output->z = simpleori->z + simpleray->z * len;
}

void		sub_vector(t_vector *output,
			   t_vector *one,
			   t_vector *two)
{
  output->x = one->x - two->x;
  output->y = one->y - two->y;
  output->z = one->z - two->z;
}
