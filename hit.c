/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 16:13:51 by cbesse            #+#    #+#             */
/*   Updated: 2018/03/13 14:39:29 by cbesse           ###   ########.fr       */
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

	oc = v_less(ray->A, sphere->center);
	a = v_dot(ray->B, ray->B);
	b = 2.0 * v_dot(oc, ray->B);
	c = v_dot(oc, oc) - sphere->radius * sphere->radius;
	delta = b * b - 4 * a * c;
	if (delta > 0)
	{
		temp = (-1 * b -sqrt(delta) )/ (2 * a);
		if (temp < min_max[1] && temp > min_max[0])
		{
			rec->t = temp;
			rec->p = v_add(ray->A, v_mult(ray->B, rec->t));
			rec->normal = v_div(v_less(rec->p, sphere->center), sphere->radius);
			rec->color = v_set(sphere->color.x, sphere->color.y, sphere->color.z);
			return (1);
		}
		temp = (-1 * b +sqrt(delta) )/ (2 *a);
		if (temp < min_max[1] && temp > min_max[0])
		{
			rec->t = temp;
			rec->p = v_add(ray->A, v_mult(ray->B, rec->t));
			rec->normal = v_div(v_less(rec->p, sphere->center), sphere->radius);
			rec->color = v_set(sphere->color.x, sphere->color.y, sphere->color.z);
			return (1);
		}
	}
	return (0);
}

int hit_cylindre(t_cylindre *cylindre, t_ray *ray, float *min_max, t_record	*rec)
{
	float a;
  float b;
  float c;
  t_vecteur oc;
	float temp;
	float delta;

	oc = v_cross(cylindre->dir, ray->B);
	a = v_dot(oc, oc);
  b = 2 * v_dot(oc, v_cross(cylindre->dir, v_less(ray->A, cylindre->base)));
	oc = v_cross(cylindre->dir, v_less(ray->A, cylindre->base));
  c = v_dot(oc, oc) - cylindre->radius * cylindre->radius;
	delta = b * b - 4 * a * c;
	if (delta > 0)
	{
		temp = (-1 * b -sqrt(delta) )/ (2 * a);

		if (temp < min_max[1] && temp > min_max[0])
		{
			rec->t = temp;
			rec->color = v_set(cylindre->color.x, cylindre->color.y, cylindre->color.z);
			return (1);
		}
		temp = (-1 * b +sqrt(delta) )/ (2 *a);
		if (temp < min_max[1] && temp > min_max[0])
		{
			rec->t = temp;
			rec->color = v_set(cylindre->color.x, cylindre->color.y, cylindre->color.z);
			return (1);
		}
	}
	return (0);
}

int hit_cone(t_cone *cone, t_ray *ray, float *min_max, t_record	*rec)
{
	float a;
  float b;
  float c;
  t_vecteur oc;
	float temp;
	float delta;
	float k;

	k = tan(cone->angle  / 2);
	k = k * k;

	oc = v_less(ray->A, cone->apex);
	a = v_dot(ray->B, ray->B) - (1 + k) * v_dot(ray->B, cone->dir) * v_dot(ray->B, cone->dir);
  b = 2 * (v_dot(ray->B, oc) - (1 + k) * v_dot(ray->B , cone->dir) * v_dot(oc, cone->dir));
  c = v_dot(oc, oc) - (1 + k) * v_dot(oc, cone->dir) * v_dot(oc, cone->dir);
	delta = b * b - 4 * a * c;
	if (delta > 0)
	{
		temp = (-1 * b -sqrt(delta) )/ (2 * a);

		if (temp < min_max[1] && temp > min_max[0])
		{
			rec->t = temp;
			rec->color = v_set(cone->color.x, cone->color.y, cone->color.z);
			return (1);
		}
		temp = (-1 * b +sqrt(delta) )/ (2 *a);
		if (temp < min_max[1] && temp > min_max[0])
		{
			rec->t = temp;
			rec->color = v_set(cone->color.x, cone->color.y, cone->color.z);
			return (1);
		}
	}
	return (0);
}

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
		rec->color = v_set(plan->color.x, plan->color.y, plan->color.z);
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

	i = 0;
	hit_anything = 0;
	closet_so_far = min_max[1];
	while(i < list[0].size)
	{
		if (list[i].type == 1)
			if(hit_sphere(list[i].form, ray, min_max, &temp_rec))
			{
				hit_anything = 1;
				closet_so_far = temp_rec.t;
				set_rec(temp_rec, rec);
				set_min_max(min_max[0], closet_so_far, min_max);
			}
		if (list[i].type == 2)
			if(hit_plan(list[i].form, ray, min_max, &temp_rec))
			{
				hit_anything = 1;
				closet_so_far = temp_rec.t;
				set_rec(temp_rec, rec);
				set_min_max(min_max[0], closet_so_far, min_max);
			}
		if (list[i].type == 3)
			if(hit_cylindre(list[i].form, ray, min_max, &temp_rec))
			{
				hit_anything = 1;
				closet_so_far = temp_rec.t;
				set_rec(temp_rec, rec);
				set_min_max(min_max[0], closet_so_far, min_max);
			}
		if (list[i].type == 4)
			if(hit_cone(list[i].form, ray, min_max, &temp_rec))
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
