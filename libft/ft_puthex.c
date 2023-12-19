/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:42:31 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 09:25:34 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned long n, int low, int cnt, int fd)
{
	char		w;
	char		*base;

	base = "0123456789abcdef";
	if (!low)
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		cnt += ft_puthex(n / 16, low, 0, fd);
		cnt += ft_puthex(n % 16, low, 0, fd);
	}
	else
	{
		w = base[n];
		write(fd, &w, 1);
		cnt++;
	}
	return (cnt);
}
