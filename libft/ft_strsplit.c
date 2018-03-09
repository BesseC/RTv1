/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:17:53 by cbesse            #+#    #+#             */
/*   Updated: 2017/12/05 16:13:58 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_mot(const char *str, char c)
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

static int	lmot(const char *str, int k, char c)
{
	int	count;

	count = 0;
	while (str[k] != c && str[k])
	{
		k++;
		count++;
	}
	return (count);
}

char		**ft_strsplit(char const *str, char c)
{
	int		i[3];
	char	**tab;

	if (!str)
		return (NULL);
	i[1] = 0;
	i[2] = 0;
	if (!(tab = ft_memalloc(sizeof(char**) * nb_mot(str, c) + 1)))
		return (0);
	while (str[i[1]] != '\0')
	{
		while (str[i[1]] == c && str[i[1]])
			i[1]++;
		if (str[i[1]] != '\0')
		{
			i[0] = 0;
			if (!(tab[i[2]] = ft_memalloc(sizeof(char*) * lmot(str, i[1], c))))
				return (0);
			while (str[i[1]] != c && str[i[1]])
				tab[i[2]][i[0]++] = str[i[1]++];
			tab[i[2]++][i[0]] = '\0';
		}
	}
	tab[i[2]] = NULL;
	return (tab);
}
