/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 18:18:32 by cbesse            #+#    #+#             */
/*   Updated: 2018/03/05 18:18:33 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void attr_sphere(t_sphere *sphere, char **tab)
{
  sphere->center.x = ft_atof(tab[1] + 1);
  sphere->center.y = ft_atof(tab[2]);
  sphere->center.z = ft_atof(tab[3]);
  sphere->radius = ft_atof(tab[4]);
}

void attr_plan(t_plan *plan, char **tab)
{
  plan->point.x = ft_atof(tab[1] + 1);
  plan->point.y = ft_atof(tab[2]);
  plan->point.z = ft_atof(tab[3]);
  plan->vdir.x = ft_atof(tab[4] + 1);
  plan->vdir.y = ft_atof(tab[5]);
  plan->vdir.z = ft_atof(tab[6]);
  plan->vdir = v_normalize(plan->vdir);
}

void attr_cylindre(t_cylindre *cylindre, char **tab)
{
  cylindre->base.x = ft_atof(tab[1] + 1);
  cylindre->base.y = ft_atof(tab[2]);
  cylindre->base.z = ft_atof(tab[3]);
  cylindre->radius = ft_atof(tab[4]);
  cylindre->dir.x = ft_atof(tab[5] + 1);
  cylindre->dir.y = ft_atof(tab[6]);
  cylindre->dir.z = ft_atof(tab[7]);
  cylindre->dir = v_normalize(cylindre->dir);
}

int set_sphere(t_scene *scene, char **tab)
{
  int j;

  j = 0;
  while(tab[j++]);
  if (j - 1 != 8)
     return(-1);
  scene->list[scene->i].form = (t_sphere *)ft_memalloc(1 * sizeof(t_sphere));
  attr_sphere(scene->list[scene->i].form, tab);
  scene->list[scene->i].color.x = ft_atof(tab[5] + 1);
  scene->list[scene->i].color.y = ft_atof(tab[6]);
  scene->list[scene->i].color.z = ft_atof(tab[7]);
  scene->list[scene->i].type = 1;
  scene->i++;
  j = 0;
  while (j < scene->i)
    scene->list[j++].size = scene->i;
  return(1);
}

int set_plan(t_scene *scene, char **tab)
{
  int j;

  j = 0;
  while(tab[j++]);
  if (j - 1 != 10)
     return(-1);
  scene->list[scene->i].form = (t_plan *)ft_memalloc(1 * sizeof(t_plan));
  attr_plan(scene->list[scene->i].form, tab);
  scene->list[scene->i].color.x = ft_atof(tab[7] + 1);
  scene->list[scene->i].color.y = ft_atof(tab[8]);
  scene->list[scene->i].color.z = ft_atof(tab[9]);
  scene->list[scene->i].type = 2;
  scene->i++;
  j = 0;
  while (j < scene->i)
    scene->list[j++].size = scene->i;
  return(1);
}

int set_cylindre(t_scene *scene, char **tab)
{
  int j;

  j = 0;
  while(tab[j++]);
  if (j - 1 != 11)
     return(-1);
  scene->list[scene->i].form = (t_cylindre *)ft_memalloc(sizeof(t_cylindre));
  attr_cylindre(scene->list[scene->i].form, tab);
  scene->list[scene->i].color.x = ft_atof(tab[8] + 1);
  scene->list[scene->i].color.y = ft_atof(tab[9]);
  scene->list[scene->i].color.z = ft_atof(tab[10]);
  scene->list[scene->i].type = 3;
  scene->i++;
  j = 0;
  while (j < scene->i)
    scene->list[j++].size = scene->i;
  return(1);
}

void attr_cone(t_cone *cone, char **tab)
{
  cone->apex.x = ft_atof(tab[1] + 1);
  cone->apex.y = ft_atof(tab[2]);
  cone->apex.z = ft_atof(tab[3]);
  cone->angle = ft_atof(tab[4]) * M_PI / 180;
  cone->dir.x = ft_atof(tab[5] + 1);
  cone->dir.y = ft_atof(tab[6]);
  cone->dir.z = ft_atof(tab[7]);
  cone->dir = v_normalize(cone->dir);
}

int set_cone(t_scene *scene, char **tab)
{
  int j;

  j = 0;
  while(tab[j++]);
  if (j - 1 != 11)
     return(-1);
  scene->list[scene->i].form = (t_cone *)ft_memalloc(sizeof(t_cone));
  attr_cone(scene->list[scene->i].form, tab);
  scene->list[scene->i].color.x = ft_atof(tab[8] + 1);
  scene->list[scene->i].color.y = ft_atof(tab[9]);
  scene->list[scene->i].color.z = ft_atof(tab[10]);
  scene->list[scene->i].type = 4;
  scene->i++;
  j = 0;
  while (j < scene->i)
    scene->list[j++].size = scene->i;
  return(1);
}

int set_light(t_scene *scene, char **tab)
{
  int j;

  j = 0;
  while(tab[j++]);
  if (j - 1 != 4)
     return(-1);
  scene->light[scene->k].x = ft_atof(tab[1] + 1);
  scene->light[scene->k].y = ft_atof(tab[2]);
  scene->light[scene->k].z = ft_atof(tab[3]);
  scene->k++;
  printf("%d\n",scene->k);
  return(1);
}

int set_cam(t_scene *scene, char **tab)
{
  int j;

  j = 0;
  while(tab[j++]);
  if (j - 1 != 7)
     return(-1);
  scene->camorigin.x = ft_atof(tab[1] + 1);
  scene->camorigin.y = ft_atof(tab[2]);
  scene->camorigin.z = ft_atof(tab[3]);
  scene->camdir.x = ft_atof(tab[4] + 1);
  scene->camdir.y = ft_atof(tab[5]);
  scene->camdir.z = ft_atof(tab[6]);
  return(1);
}

void set_min_max(double min, double max, double *min_max)
{
  min_max[0] = min;
  min_max[1] = max;
}
