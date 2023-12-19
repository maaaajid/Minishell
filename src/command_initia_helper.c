/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_initia_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 07:05:51 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/06/25 07:20:34 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_command_segments(int *original_tokens)
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
	com_count++;
	return (com_count);
}

char	***allocate_command_segments(int com_count)
{
	char	***command_segments;

	command_segments = malloc((com_count + 1) * sizeof(char **));
	if (!command_segments)
		return (NULL);
	command_segments[com_count] = NULL;
	return (command_segments);
}
