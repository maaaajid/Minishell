/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_initia.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:24:39 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 07:14:06 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**ft_subarray(char **array, int start, int length)
{
	int		i;
	char	**subarray;

	i = 0;
	subarray = malloc((length + 1) * sizeof(char *));
	if (!subarray)
		return (NULL);
	while (i < length)
	{
		subarray[i] = ft_strdup(array[start + i]);
		if (!subarray[i])
		{
			while (i--)
				free(subarray[i]);
			free(subarray);
			return (NULL);
		}
		i++;
	}
	subarray[length] = NULL;
	return (subarray);
}

static void	populate_command_segments(char **original_commands
		, int *original_tokens, char ***command_segments)
{
	int	i;
	int	j;
	int	s;

	i = 0;
	j = 0;
	s = 0;
	while (original_tokens[i] != NULL_TOKEN)
	{
		if (original_tokens[i] == PIPELINE)
		{
			command_segments[j] = ft_subarray(original_commands, s, i - s);
			s = i + 1;
			j++;
		}
		i++;
	}
	command_segments[j] = ft_subarray(original_commands, s, i - s);
}

char	***split_cmd(char **commands, int *tokens)
{
	int		com_count;
	char	***command_segments;

	com_count = count_command_segments(tokens);
	command_segments = allocate_command_segments(com_count);
	if (!command_segments)
		return (NULL);
	populate_command_segments(commands, tokens, command_segments);
	return (command_segments);
}

t_command	*initialize_command_segments(t_command *c)
{
	c->command_segments = split_cmd(c->original_commands, c->original_tokens);
	if (!c->command_segments)
		printf("command segments initialization failed");
	c->token_types = split_tokens(c->original_tokens);
	if (!c->token_types)
		printf("token type initialization failed");
	return (c);
}

t_command	*command_ini(char *op_com, t_env *env)
{
	t_command	*command;

	op_com = input_parse_op(op_com);
	if (!op_com)
		return (NULL);
	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->original_commands = splt_commands(op_com);
	free(op_com);
	if (!command->original_commands)
		return (free(command), NULL);
	command->original_tokens = tokenization(command->original_commands);
	if (!command->original_tokens)
	{
		ft_free((void **)command->original_commands);
		free(command);
		return (NULL);
	}
	expand_env(command->original_commands, command->original_tokens, env);
	del_quotes(command->original_commands);
	command = initialize_command_segments(command);
	return (command);
}
