/*
** misc.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:23:54 2016 marc brout
** Last update Thu Feb 25 16:23:57 2016 marc brout
*/

int	my_strlen(char	*str)
{
  int	i;

  i = 0;
  while (str && str[i])
    i++;
  return (i);
}
