/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:40:45 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 09:00:48 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	*ft_subarray_int(int *array, int start, int length)
{
	int	i;
	int	*subarray;

	i = 0;
	subarray = malloc((length + 1) * sizeof(int));
	if (!subarray)
		return (NULL);
	while (i < length)
	{
		subarray[i] = array[start + i];
		i++;
	}
	subarray[length] = NULL_TOKEN;
	return (subarray);
}

static int	count_pipelines(int *original_tokens)
{
	int	i;
	int	com_count;

	i = 0;
	com_count = 0;
	while (original_tokens[i] != NULL_TOKEN)
	{
		if (original_tokens[i] == PIPELINE)
			com_count++;
		i++;
	}
	return (com_count + 1);
}

int	**split_tokens(int *original_tokens)
{
	int	i;
	int	j;
	int	start;
	int	**token_types;
	int	com_count;

	i = -1;
	j = 0;
	start = 0;
	com_count = count_pipelines(original_tokens);
	token_types = malloc((com_count + 1) * sizeof(int *));
	if (!token_types)
		return (NULL);
	token_types[com_count] = NULL;
	while (original_tokens[++i] != NULL_TOKEN)
	{
		if (original_tokens[i] == PIPELINE)
		{
			token_types[j] = ft_subarray_int(original_tokens, start, i - start);
			start = i + 1;
			j++;
		}
	}
	token_types[j] = ft_subarray_int(original_tokens, start, i - start);
	return (token_types);
}
