/*
** my_getnbr.c for my_getnbr.c in /home/brout_m/rendu/Piscine_C_J10
**
** Made by marc brout
** Login   <brout_m@epitech.net>
**
** Started on  Mon Oct 12 19:01:57 2015 marc brout
** Last update Thu Feb 25 16:17:28 2016 marc brout
*/

int		neg(const char *str)
{
  int		i;
  int		isneg;

  i = 0;
  isneg = 1;
  while ((str[i] == '-') || (str[i] == '+'))
    {
      if (str[i] == '-')
	isneg = -isneg;
      i = i + 1;
    }
  return (isneg);
}

int		my_getnbr(const char *str)
{
  int		total;
  int		isneg;
  int		i;

  if (!str || str[0] == 0)
    return (0);
  i = 0;
  isneg = 1;
  while ((str[i] == '-') || (str[i] == '+'))
    {
      if (str[i] == '-')
	isneg = -isneg;
      i = i + 1;
    }
  total = 0;
  while ((str[i] >= '0') && (str[i] <= '9'))
    {
      total = ((total * 10) + (str[i] - 48));
      i = i + 1;
    }
  return (total * isneg);
}


double		my_getdouble(const char *str)
{
  double	total;
  double	dec;
  int		i;
  int		isneg;
  int		power;

  if (!str || str[0] == 0)
    return (0);
  isneg = neg(str);
  total = my_getnbr(str) * isneg;
  i = -1;
  while (str[++i] && str[i] != '.');
  i++;
  dec = 0;
  power = 1;
  while ((str[i] >= '0') && (str[i] <= '9'))
    {
      dec = ((dec * 10) + (str[i] - 48));
      power *= 10;
      i = i + 1;
    }
  return ((total + (dec / power)) * isneg);
}
