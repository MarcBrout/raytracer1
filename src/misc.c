/*
** misc.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1/src
**
** Made by
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 12:22:07 2016
** Last update Thu Feb 25 12:23:01 2016 
*/

int	my_strlen(char	*str)
{
  int	i;

  i = 0;
  while (str && str[i])
    i++;
  return (i);
}
