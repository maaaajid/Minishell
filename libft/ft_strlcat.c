/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 09:40:30 by lahamoun          #+#    #+#             */
/*   Updated: 2022/11/05 15:39:51 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_d;
	size_t	len_s;

	if (size == 0)
		return (ft_strlen(src));
	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	i = 0;
	j = 0;
	if (size <= len_d)
		return (size + ft_strlen(src));
	while (dst[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0' && i < size - 1)
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (len_d + len_s);
}
