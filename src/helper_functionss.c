/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functionss.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 02:16:05 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 08:30:33 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strjoin_many(int num_args, ...)
{
	va_list	ap;
	char	*res;
	char	*temp;
	char	*arg;
	int		i;

	i = 0;
	va_start(ap, num_args);
	res = ft_strdup("");
	while (i < num_args)
	{
		arg = va_arg(ap, char *);
		temp = ft_strjoin(res, arg);
		free(res);
		res = temp;
		i++;
	}
	va_end(ap);
	return (res);
}

char	*ft_strjoin_char(const char *s1, const char *s2, char c)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	char	*new_str;

	len_s1 = 0;
	len_s2 = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[len_s1])
		len_s1++;
	while (s2[len_s2])
		len_s2++;
	new_str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 2));
	if (!new_str)
		return (NULL);
	while (*s1)
		new_str[i++] = *s1++;
	new_str[i++] = c;
	while (*s2)
		new_str[i++] = *s2++;
	new_str[i] = '\0';
	return (new_str);
}

void	ft_free(void **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
