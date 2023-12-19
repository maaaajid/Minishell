/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:45:37 by lahamoun          #+#    #+#             */
/*   Updated: 2022/11/09 04:04:47 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cw(char const *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			while (str[i] && str[i] != c)
				i++;
			j++;
		}
	}
	return (j);
}

static int	ft_clen(char const *str, int i, char c)
{
	int	j;

	j = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		j++;
	}
	return (j);
}

static void	ft_remp(char const *str, char **tab, int *i, char c)
{
	int	j;
	int	k;

	k = 0;
	j = 0;
	while (str[*i] && str[*i] != c)
	{
		tab[k][j] = str[*i];
		(*i)++;
		j++;
	}
	tab[k][j] = '\0';
}

static char	**ft_free(char **tab, int k)
{
	while (k >= 0)
	{
		free(tab[k]);
		k--;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_cw(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			tab[k] = malloc(sizeof(char) * (ft_clen(s, i, c) + 1));
			if (!(tab[k]))
				return (ft_free(tab, k - 1));
			ft_remp(s, &tab[k++], &i, c);
		}
	}
	tab[k] = NULL;
	return (tab);
}
