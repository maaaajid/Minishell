/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:45:40 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 09:48:22 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*dst;
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (src[len] != '\0' && len < n)
		len++;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[len] = '\0';
	return (dst);
}
