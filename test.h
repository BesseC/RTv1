/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 11:47:09 by cbesse            #+#    #+#             */
/*   Updated: 2018/03/01 11:47:38 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# include "mlx.h"
# include "libft/includes/libft.h"
# include <math.h>
# define W_LENGHT 900
# define W_WIDTH 450
# define N_FORM 3

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;
typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}				t_mlx;
typedef struct s_vecteur
{
	float x;
	float y;
	float z;
}								t_vecteur;
typedef struct s_record
{
	float t;
	t_vecteur p;
	t_vecteur normal;
	t_vecteur color;
	int hit_anything;
}								t_record;
typedef struct s_ray
{
	t_vecteur A;
	t_vecteur B;
}								t_ray;
typedef struct s_sphere
{
	t_vecteur center;
	float radius;
	t_vecteur color;
}								t_sphere;
typedef struct s_plan
{
	t_vecteur point;
	t_vecteur vdir;
	t_vecteur color;
}								t_plan;
typedef struct s_formlist
{
	void *form;
	int type;
	int size;
}				t_formlist;

t_vecteur v_add(t_vecteur v1, t_vecteur v2);
t_vecteur v_less(t_vecteur v1, t_vecteur v2);
t_vecteur v_cross(t_vecteur v1, t_vecteur v2);
float v_dot(t_vecteur v1, t_vecteur v2);
float v_norm(t_vecteur v);
t_vecteur v_mult(t_vecteur v1, float i);
int v_equal(t_vecteur v1, t_vecteur v2);
t_vecteur v_div(t_vecteur v1, float i);
t_vecteur v_set(float x, float y, float z);
t_vecteur v_normalize(t_vecteur v);
void	mlx_set(t_mlx *mlx);
int		my_key_funct(int keycode);
void set_sphere(t_sphere *sphere, t_vecteur a, float b,  t_vecteur c );
void set_min_max(float min, float max, float *min_max);
int hit_sphere(t_sphere *sphere, t_ray *ray, float *min_max, t_record *rec);
int hit_qqch(t_formlist *list, t_ray *ray, float *min_max, t_record *rec);
t_formlist *set_list(void);
void set_rec(t_record r, t_record *rec);
#endif
