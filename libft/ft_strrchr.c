/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:58:28 by lahamoun          #+#    #+#             */
/*   Updated: 2022/11/02 12:38:36 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	t;

	t = (char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == t)
			return ((char *)s + i);
		i--;
	}
	return (0);
}
