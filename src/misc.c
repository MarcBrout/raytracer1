/*
** misc.c for rt in /home/brout_m/RENDU/INFOGRAPHIE/gfx_raytracer1
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Thu Feb 25 16:23:54 2016 marc brout
** Last update Thu Mar 10 12:41:16 2016 marc brout
*/

int	my_strcmp(char *str1, char *str2)
{
  int	i;

  i = 0;
  if (!str1 || !str2)
    return (1);
  while (str1[i] && str2[i] && str1[i] == str2[i])
    i += 1;
  return (str1[i] - str2[i]);
}

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str && str[i])
    i++;
  return (i);
}
