/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 02:16:05 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 07:27:17 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	com_cnt(char **args, int *tokens)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (args[i] && tokens[i])
	{
		if (tokens[i] == PIPELINE)
			cnt++;
		i++;
	}
	return (cnt + 1);
}

void	ft_free_command(t_command *command, char *path, char **args)
{
	int	i;

	free (path);
	ft_free((void **)args);
	i = 0;
	while (command->command_segments[i])
		ft_free((void **)command->command_segments[i++]);
	free(command->command_segments);
	ft_free((void **)command->token_types);
	free(command->original_tokens);
	ft_free((void **)command->original_commands);
	free(command->hold_pid);
	free(command);
}

void	ft_list_clear(t_env **env)
{
	t_env	*ptr;
	t_env	*tmp;

	if (!*env)
		return ;
	ptr = *env;
	while (ptr != NULL)
	{
		tmp = ptr;
		ptr = ptr->next;
		free (tmp->name);
		if (tmp->value)
			free (tmp->value);
		free (tmp);
	}
	*env = NULL;
}

void	close_all(int pipe_fd[2][2], int com_cnt)
{
	close_fd(pipe_fd[(com_cnt + 1) % 2][0]);
	close_fd(pipe_fd[com_cnt % 2][0]);
	close_fd(pipe_fd[com_cnt % 2][1]);
}
