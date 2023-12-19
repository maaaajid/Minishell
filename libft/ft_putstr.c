/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:38:05 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/24 17:38:28 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str, int fd)
{
	int	c;

	c = 0;
	if (!str)
	{
		write(fd, "(null)", 6);
		return (6);
	}	
	while (str[c])
	{
		write(fd, &str[c], 1);
		c++;
	}
	return (c);
}
