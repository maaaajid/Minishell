/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 00:34:12 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/06/22 00:37:10 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	args_number(int *tokens)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i] == COM_ARGUMENT || tokens[i] == COM_NAME)
			j++;
		i++;
	}
	return (j);
}

char	**command_args(char **c_args, int *tokens, t_env *env, char *cmd)
{
	char	**args;
	int		i;
	int		na;

	args = split_path(env);
	if (!args && env && !cmd)
		return (NULL);
	ft_free((void **)args);
	na = args_number(tokens);
	if (!na)
		return (NULL);
	args = malloc(sizeof(char *) * (na + 1));
	if (!args)
		return (NULL);
	args[na] = NULL;
	i = -1;
	na = 0;
	while (c_args[++i])
		if (tokens[i] == COM_NAME || tokens[i] == COM_ARGUMENT)
			args[na++] = ft_strdup(c_args[i]);
	return (args);
}

int	check_env_buil(char **cmd_array, int *token_array)
{
	int	i;

	i = 0;
	while (cmd_array && cmd_array[i] && token_array
		&& token_array[i] != COM_NAME)
		i++;
	if (!cmd_array[i])
		return (0);
	if (!ft_strcmp(cmd_array[i], "cd")
		|| !ft_strcmp(cmd_array[i], "export")
		|| !ft_strcmp(cmd_array[i], "unset")
		|| !ft_strcmp(cmd_array[i], "exit"))
		return (1);
	return (0);
}
