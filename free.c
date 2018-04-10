/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:52:22 by cbesse            #+#    #+#             */
/*   Updated: 2018/04/05 15:52:24 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vecteur libe(void **r,  void **min_max, t_vecteur vr)
{
  ft_memdel(r);
  ft_memdel(min_max);
  return(vr);
}

void tab_free(char **tab, char *line)
{
  int i;
  int k;

  i = -1;
  k = ft_nmotsplit(line, ' ');
  while(++i < k && tab[i])
    ft_memdel((void **)&tab[i]);
  ft_memdel((void **)&tab);
  ft_memdel((void **)&line);
}

void printexit(void)
{
  ft_putendl_fd("Erreur de fichier de configuration", 2);
  exit(1);
}
