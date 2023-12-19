/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:54:30 by lahamoun          #+#    #+#             */
/*   Updated: 2022/11/09 05:00:58 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;

	str = malloc (sizeof(char) * ft_strlen(s1) + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy (str, s1, ft_strlen(s1) + 1);
	return (str);
}
