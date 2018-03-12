/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:13:51 by cbesse            #+#    #+#             */
/*   Updated: 2018/03/09 16:13:54 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int hit_sphere(t_sphere *sphere, t_ray *ray, float *min_max, t_record *rec)
{
	t_vecteur oc;
	float a;
	float b;
	float c;
	float delta;
	float temp;

//ft_putstr("/ndebut hit");
	oc = v_less(ray->A, sphere->center);
	a = v_dot(ray->B, ray->B);
	b = 2.0 * v_dot(oc, ray->B);
	c = v_dot(oc, oc) - sphere->radius * sphere->radius;
	delta = b * b - 4 * a * c;
	if (delta > 0)
	{
		temp = (-b -sqrt(delta) )/ (2 * a);
		if (temp < min_max[1] && temp > min_max[0])
			{
				rec->t = temp;
				rec->p = v_add(ray->A, v_mult(ray->B, rec->t));
				rec->normal = v_div(v_less(rec->p, sphere->center), sphere->radius);
				rec->color = v_set(sphere->color.x, sphere->color.y, sphere->color.z);
//printf("x = %f, y = %f, z = %f\n", rec->normal.x , rec->normal.y , rec->normal.z);
        return (1);
			}
			temp = (-b +sqrt(delta) )/ (2 *a);
			if (temp < min_max[1] && temp > min_max[0])
				{
					rec->t = temp;
					rec->p = v_add(ray->A, v_mult(ray->B, rec->t));
					rec->normal = v_div(v_less(rec->p, sphere->center), sphere->radius);
					rec->color = v_set(sphere->color.x, sphere->color.y, sphere->color.z);
//printf("x = %f, y = %f, z = %f\n", rec->normal.x , rec->normal.y , rec->normal.z);
					return (1);
				}
	}
	return (0);
}
/*
int hit_cylindre(t_cylindre *cylindre, t_ray *ray, float *min_max, t_record	*rec)
{
	float a;
	float b;
	float c;
	t_vecteur oc;
	oc = v_less(ray->A, cylindre->center);
	a = ray->B.x * ray->B.x +0 ray->B.z * ray->B.z;
	b = ray->B.x * oc.x + ray->B.z * oc.z;
	c = oc.x * oc.x + oc.z * oc.z - radius * radius;
}
*/
int hit_plan(t_plan *plan, t_ray *ray, float *min_max, t_record *rec)
{
	t_vecteur oc;
	float d;
	float temp;
	d = -(plan->vdir.x * plan->point.x + plan->vdir.y * plan->point.y + plan->vdir.z * plan->point.z);

	oc = v_less(ray->A, plan->point);



	temp =  -((oc.x * plan->vdir.x + oc.y * plan->vdir.y + oc.z * plan->vdir.z + d) /
					(plan->vdir.x * ray->B.x + plan->vdir.y * ray->B.y + plan->vdir.z * ray->B.z));
	if (temp < min_max[1] && temp > min_max[0])
	{
			rec->t = temp;
			//rec->p = v_add(ray->A, v_mult(ray->B, rec->t));
			//rec->normal = v_div(v_less(rec->p, sphere->center), sphere->radius);
			rec->color = v_set(plan->color.x, plan->color.y, plan->color.z);
			//printf("x = %f, y = %f, z = %f\n", rec->normal.x , rec->normal.y , rec->normal.z);
			return (1);
		}



	return (0);
}

int hit_qqch(t_formlist *list, t_ray *ray, float *min_max, t_record *rec)
{
  int i;
  t_record temp_rec;
  int hit_anything;
  double closet_so_far;
//ft_putstr("/ndebut hit");
  i = 0;
  hit_anything = 0;
  closet_so_far = min_max[1];
  while(i < list[0].size)
  {
    if (list[i].type == 1)
      if(hit_sphere(list[i].form, ray, min_max, &temp_rec))
      {
  //  ft_putstr("apres hit_sphere");
    hit_anything = 1;
    closet_so_far = temp_rec.t;
    set_rec(temp_rec, rec);
  //  printf("x = %f, y = %f, z = %f\n", rec->normal.x , rec->normal.y , rec->normal.z);
  //  ft_putstr("set_rec");
	//printf("VRx = %f, VRy = %f, VRz = %f\n",rec->color.x, rec->color.y , rec->color.z);
    set_min_max(min_max[0], closet_so_far, min_max);
		//printf("VRx = %f, VRy = %f, VRz = %f\n",rec->color.x, rec->color.y , rec->color.z);
  		}
			if (list[i].type == 2)
	      if(hit_plan(list[i].form, ray, min_max, &temp_rec))
	      {
	    	hit_anything = 1;
	    	closet_so_far = temp_rec.t;
	    	set_rec(temp_rec, rec);
	    	set_min_max(min_max[0], closet_so_far, min_max);
	  		}
    i++;
  }
  return(hit_anything);
}
