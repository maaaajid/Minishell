/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:25:33 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 09:27:03 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wach_flag(const char *a)
{
	char	*id;

	id = "cspdiuxX%";
	if (*a != '%')
		return (0);
	while (*id)
	{
		if (*(a + 1) == *id++)
			return (1);
	}
	return (0);
}

static int	toks(char c, va_list GG, int ab, int fd)
{
	if (c == 'd' || c == 'i')
		ab = ft_putnbr(va_arg(GG, int), ab, fd);
	if (c == 'u')
		ab = ft_putnbr(va_arg(GG, unsigned), ab, fd);
	if (c == 'p')
		ab += ft_putptr(va_arg(GG, unsigned long), fd);
	if (c == 'x' || c == 'X')
		ab = ft_puthex(va_arg(GG, unsigned), c == 'x', ab, fd);
	if (c == 'c')
		ab += ft_putchar(va_arg(GG, int), fd);
	if (c == 's')
		ab += ft_putstr(va_arg(GG, char *), fd);
	if (c == '%')
		ab += ft_putchar('%', fd);
	return (ab);
}

int	ft_printf(int fd, const char *args, ...)
{
	int		ab;
	va_list	gg;

	ab = 0;
	va_start(gg, args);
	while (*args)
	{
		if (wach_flag(args))
		{
			ab = toks(*(args + 1), gg, ab, fd);
			args++;
		}
		else
			ab += ft_putchar(*args, fd);
		args++;
	}
	va_end(gg);
	return (ab);
}
