/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:09:21 by lahamoun          #+#    #+#             */
/*   Updated: 2022/11/05 14:26:38 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	if (!src && len == 0)
		return (dst);
	if (!src && !dst)
		return (dst);
	if (dst == src)
		return (dst);
	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	if (a > b)
	{
		while (len > i)
		{
			a[len - 1] = b[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
