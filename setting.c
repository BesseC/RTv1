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

void set_sphere(t_sphere *sphere, t_vecteur a, float b)
{
  sphere->center = a;
  sphere->radius = b;
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
  while(++i < N_FORM)
    list[i].form = (t_sphere *)ft_memalloc(1 * sizeof(t_sphere));
//  ft_putstr("/napres malloc");
  set_sphere(list[0].form, v_set(0.0, 0.0, -1.0), 0.5);
  set_sphere(list[1].form, v_set(1.5, 0.3, -2.0), 0.5);
//  ft_putstr("/nfin set sphere");
  //list[0].form = &sphere1;
  list[0].size = 2;
  list[0].type = 1;
  list[1].size = 2;
  list[1].type = 1;
  return (list);
}

t_record *set_rec(t_record r)
{
  t_record *rec;

  rec = (t_record*) ft_memalloc(sizeof(t_record));
  rec->t = r.t;
  rec->p = r.p;
  //printf("x = %f, y = %f, z = %f\n", r.normal.x , r.normal.y , r.normal.z);
  rec->normal = r.normal;
  return (rec);
}
