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

#include "test.h"

void set_sphere(t_sphere *sphere, t_vecteur a, float b,  t_vecteur c )
{
  sphere->center = a;
  sphere->radius = b;
  sphere->color = c;
}

void set_cylindre(t_cylindre *cylindre, t_vecteur a, float b,  t_vecteur c )
{
  cylindre->base = a;
  cylindre->radius = b;
  cylindre->dir = c;
  cylindre->color = v_set(0.99, 0.0, 0.99);
}

void set_cone(t_cone *cylindre, t_vecteur a, float b,  t_vecteur c )
{
  b = b * M_PI / 180;
  cylindre->apex = a;
  cylindre->angle = b;
  cylindre->dir = c;
  cylindre->color = v_set(0.99, 0.99, 0.0);
}

void set_plan(t_plan *plan, t_vecteur a, t_vecteur b,  t_vecteur c )
{
  plan->point = a;
  plan->vdir = b;
  plan->color = c;
}

void set_min_max(float min, float max, float *min_max)
{
  min_max[0] = min;
  min_max[1] = max;
}

t_formlist *set_list(void)
{
  t_formlist *list;
  t_sphere sphere1;
  int i = -1;
  //ft_putstr("/ndebut set_list");
  list = (t_formlist *)ft_memalloc(N_FORM * sizeof(t_formlist));
  list[3].form = (t_cylindre *)ft_memalloc(1 * sizeof(t_cylindre));
  set_cylindre(list[3].form, v_set(0.0, 0.0, -1.0), 0.3,  v_set(-1, 1, 0) );
  list[3].size = N_FORM;
  list[3].type = 3;
  while(++i < 2)
    list[i].form = (t_sphere *)ft_memalloc(1 * sizeof(t_sphere));
    list[2].form = (t_plan *)ft_memalloc(1 * sizeof(t_plan));
//------------2 SPHERE + 1 PLAN
  set_sphere(list[0].form, v_set(0.0, 0.0, -1.0), 0.5,  v_set(0.99, 0.0, 0.0) );
  set_sphere(list[1].form, v_set(0.0, 1.0, -2.0), 0.75,  v_set(0.0, 0.99, 0.0) );
  set_plan(list[2].form, v_set(0.0, 0.5, -1.0), v_set(-0.2, -1.0, -0.75),  v_set(0.0, 0.0, 0.99));
//------------CYLINDRE
  list[3].form = (t_cylindre *)ft_memalloc(1 * sizeof(t_cylindre));
  set_cylindre(list[3].form, v_set(0.0, 0.0, -1.0), 0.3,  v_set(-1, 1, 0) );
  list[3].size = N_FORM;
  list[3].type = 3;
//------------CONE
  list[4].form = (t_cone *)ft_memalloc(1 * sizeof(t_cone));
  set_cone(list[4].form, v_set(1.0, 1.0, -1.0), 30,  v_set(0, 1, 1) );
  list[4].size = N_FORM;
  list[4].type = 4;

  //list[0].form = &sphere1;
  list[0].size = N_FORM;
  list[0].type = 1;
  list[1].size = N_FORM;
  list[1].type = 1;
  list[2].size = N_FORM;
  list[2].type = 2;
  return (list);
}

void set_rec(t_record r, t_record *rec)
{
  rec->t = r.t;
  rec->p = v_set(r.p.x, r.p.y, r.p.z);
  rec->normal = v_set(r.normal.x, r.normal.y, r.normal.z);
  rec->color = v_set(r.color.x, r.color.y, r.color.z);
}
