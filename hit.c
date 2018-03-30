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

int hit_sphere(t_sphere *sphere, t_ray *ray, double *min_max, t_record *rec)
{
	t_vecteur oc;
	double tab[5];

	oc = v_less(ray->A, sphere->center);
	tab[0] = v_dot(ray->B, ray->B);
	tab[1] = 2.0 * v_dot(oc, ray->B);
	tab[2] = v_dot(oc, oc) - sphere->radius * sphere->radius;
	tab[3] = tab[1] * tab[1] - 4 * tab[0] * tab[2];
	if (tab[3] > 0)
	{
		tab[4] = (-1 * tab[1] - sqrt(tab[3])) / (2 * tab[0]);
		if (tab[4] < min_max[1] && tab[4] > min_max[0])
		{
			sphere_rec(ray, tab[4], sphere, rec);
			return (1);
		}
		tab[4] = (-1 * tab[1] + sqrt(tab[3])) / (2 * tab[0]);
		if (tab[4] < min_max[1] && tab[4] > min_max[0])
		{
			sphere_rec(ray, tab[4], sphere, rec);
			return (1);
		}
	}
	return (0);
}

int hit_cylindre(t_cylindre *cyl, t_ray *ray, double *min_max, t_record	*rec)
{
  t_vecteur oc;
	double tab[5];

	oc = v_cross(cyl->dir, ray->B);
	tab[0] = v_dot(oc, oc);
  tab[1] = 2 * v_dot(oc, v_cross(cyl->dir, v_less(ray->A, cyl->base)));
	oc = v_cross(cyl->dir, v_less(ray->A, cyl->base));
  tab[2] = v_dot(oc, oc) - cyl->radius * cyl->radius;
	tab[3] = tab[1] * tab[1] - 4 * tab[0] * tab[2];
	if (tab[3] > 0)
	{
		tab[4] = (-1 * tab[1] -sqrt(tab[3])) / (2 * tab[0]);
		if (tab[4] < min_max[1] && tab[4] > min_max[0])
		{
			cyl_rec(ray, tab[4], cyl, rec);
			return (1);
		}
		tab[4] = (-1 * tab[1] + sqrt(tab[3])) / (2 * tab[0]);
		if (tab[4] < min_max[1] && tab[4] > min_max[0])
		{
			cyl_rec(ray, tab[4], cyl, rec);
			return (1);
		}
	}
	return (0);
}

int hit_cone(t_cone *cone, t_ray *ray, double *min_max, t_record	*rec)
{
	double *tab;

	tab = cone_tab(cone, ray);
	if (tab[4] > 0)
	{
		tab[3] = (-1 * tab[1] -sqrt(tab[4]) )/ (2 * tab[0]);
		if (tab[3] < min_max[1] && tab[3] > min_max[0])
		{
			cone_rec(ray, tab[3], cone, rec);
			ft_memdel((void **)&tab);
			return (1);
		}
		tab[3] = (-1 * tab[1] +sqrt(tab[4]) )/ (2 * tab[0]);
		if (tab[3] < min_max[1] && tab[3] > min_max[0])
		{
			cone_rec(ray, tab[3], cone, rec);
			ft_memdel((void **)&tab);
			return (1);
		}
	}
	ft_memdel((void **)&tab);
	return (0);
}

int hit_plan(t_plan *plan, t_ray *ray, double *min_max, t_record *rec)
{
	t_vecteur oc;
	double d;
	double temp;

	d = -(plan->vdir.x * plan->point.x + plan->vdir.y * plan->point.y +
		plan->vdir.z * plan->point.z);
	oc = v_less(ray->A, plan->point);
	temp = -((oc.x * plan->vdir.x + oc.y * plan->vdir.y + oc.z * plan->vdir.z
		+ d) / (plan->vdir.x * ray->B.x + plan->vdir.y * ray->B.y +
		plan->vdir.z * ray->B.z));
	if (temp < min_max[1] && temp > min_max[0])
	{
		rec->t = temp;
		rec->p = v_add(ray->A, v_mult(ray->B, rec->t));
		rec->normal = v_normalize(v_set(plan->vdir.x, plan->vdir.y,
			plan->vdir.z));

		return (1);
	}
	return (0);
}

int hit_qqch(t_formlist *list, t_ray *ray, double *min_max, t_record *rec)
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
				rec->color = v_set(list[i].color.x, list[i].color.y, list[i].color.z);
			}
		if (list[i].type == 2)
			if(hit_plan(list[i].form, ray, min_max, &temp_rec))
			{
				hit_anything = 1;
				closet_so_far = temp_rec.t;
				set_rec(temp_rec, rec);
				set_min_max(min_max[0], closet_so_far, min_max);
				rec->color = v_set(list[i].color.x, list[i].color.y, list[i].color.z);
			}
		if (list[i].type == 3)
			if(hit_cylindre(list[i].form, ray, min_max, &temp_rec))
			{
				hit_anything = 1;
				closet_so_far = temp_rec.t;
				set_rec(temp_rec, rec);
				set_min_max(min_max[0], closet_so_far, min_max);
				rec->color = v_set(list[i].color.x, list[i].color.y, list[i].color.z);
			}
		if (list[i].type == 4)
			if(hit_cone(list[i].form, ray, min_max, &temp_rec))
			{
				hit_anything = 1;
				closet_so_far = temp_rec.t;
				set_rec(temp_rec, rec);
				set_min_max(min_max[0], closet_so_far, min_max);
				rec->color = v_set(list[i].color.x, list[i].color.y, list[i].color.z);
			}
		i++;
	}
	return(hit_anything);
}
