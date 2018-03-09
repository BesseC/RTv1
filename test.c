/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 11:47:00 by cbesse            #+#    #+#             */
/*   Updated: 2018/03/01 11:47:02 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "test.h"

t_vecteur r_color(t_ray *ray)
{
	t_vecteur unit_dir;
	float t;
	t_vecteur v2;
	t_vecteur v1;
  t_vecteur vr;
	t_vecteur center;
	t_vecteur N;
	t_vecteur rayon;
	t_sphere sphere;
	t_record *r;
	float *min_max;

	if(!(min_max = (float *)ft_memalloc(2 * sizeof(float))))
		return(v_set(0.0, 0.0, 0.0));
	center = v_set(0.0, 0.0, -1.0);
	//set_sphere(&sphere, center, 0.5);
	set_min_max(0.0, 2147483647.0, min_max);
	//ft_putstr("debut couleur");
	if (hit_qqch(set_list(), ray, min_max, r))
	{
		//rayon = v_add(ray->A, v_mult(ray->B, r.t));
		//N = v_normalize(v_less(rayon, center));
//printf("t = %f\n", r->t);
//printf("Nx = %f, Ny = %f, Nz = %f -------- ", N.x , N.y , N.z);
		N = v_set(r->normal.x + 1, r->normal.y +1 , r->normal.z + 1);
		//printf("Nx = %f, Ny = %f, Nz = %f -------- ", N.x , N.y , N.z);
		vr = v_mult(N, 0.5);
		//vr = v_set(1.0, 0.0, 0.0);
	//	printf("VRx = %f, VRy = %f, VRz = %f\n", vr.x , vr.y , vr.z);
		return(vr);
	}
	v1 = v_set(1.0, 1.0, 1.0);
 	v2 = v_set(0.5, 0.7, 1.0);

	unit_dir = ray->B;
	t = 0.5 * (unit_dir.y + 1.0);
 vr = v_add(v_mult(v1, (1.0 - t)), v_mult(v2, t));
 return (vr);
}

int main(void)
{
  t_mlx mlx;
	t_vecteur couleur;
  float i;
	int n = 0;
	int ir;
	int ig;
	int ib;
	float u;
	float v;
	t_vecteur lower_left_corner;
	t_vecteur horizontal;
	t_vecteur vertical;
	t_vecteur origin;
	t_vecteur temp[3];
	t_ray ray;
	float j = W_WIDTH - 1;

	lower_left_corner = v_set(-2.0, -1.0, -1.0);
	horizontal = v_set(4.0, 0.0, 0.0);
	vertical = v_set(0.0, 2.0, 0.0);
	origin = v_set(0.0, 0.0, 0.0);
  mlx_set(&mlx);
  while (j >= 0)
  {
		i = 0;
      while (i < W_LENGHT)
			{
				u = (float)i / (float)W_LENGHT;
				v = (float)j / (float)W_WIDTH;
				ray.A = origin;
				temp[0] = v_mult(horizontal, u);
				temp[1] = v_mult(vertical, v);
				temp[2] = v_add(lower_left_corner, temp[0]);
				ray.B = v_add(temp[1], temp[2]);
				couleur = r_color(&ray);
				ir = (int)(255.99 * couleur.x);
				ig = (int)(255.99 * couleur.y);
				ib = (int)(255.99 * couleur.z);
				mlx.img.data[n] = ir * 256 * 256 + ig * 256 + ib;
				n++;
				i++;
			}
			j--;
  }
  mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img_ptr, 0, 0);
  mlx_key_hook(mlx.win, my_key_funct, &mlx);
  mlx_loop(mlx.mlx);
}
