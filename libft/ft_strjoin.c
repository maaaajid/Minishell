/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:07:30 by lahamoun          #+#    #+#             */
/*   Updated: 2022/11/02 15:05:54 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*s3;

	if (!s1 || !s2)
		return (0);
	s3 = malloc((ft_strlen(s2) + ft_strlen(s1) + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != 0)
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
		s3[i++] = s2[j++];
	s3[i] = 0;
	return (s3);
}
