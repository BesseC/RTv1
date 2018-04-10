/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 15:49:10 by cbesse            #+#    #+#             */
/*   Updated: 2018/04/06 15:49:12 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int	ft_nmotsplit(const char *str, char c)
{
	int v;
	int total;

	v = 0;
	total = 0;
	while (str[v])
	{
		while (str[v] != c && str[v])
			v++;
		if (str[v] == c)
		{
			total++;
		}
		v++;
	}
	return (total);
}
