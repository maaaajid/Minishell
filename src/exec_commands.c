/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:02:36 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/26 03:05:34 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_directory(char *command)
{
	DIR	*dirp;

	if (!command)
		return (0);
	dirp = opendir(command);
	if (dirp)
	{
		ft_printf(2, "minishell: %s: Is a directory\n", command);
		g_exit_status = 126;
		closedir(dirp);
		return (1);
	}
	return (0);
}

void	execute_commands(char **tokens, int com_cnt, char *path,
	t_command *command)
{
	char	**env;

	if (command->pipeline[(com_cnt + 1) % 2][0] == -1
		|| command->pipeline[com_cnt % 2][1] == -1
		|| !tokens || is_directory(tokens[0]))
		return ;
	if (path == NULL && tokens[0])
	{
		ft_printf(2, "minishell: %s: command not found\n", tokens[0]);
		return ;
	}
	ft_signals(PAR_SEGNAL);
	command->hold_pid[com_cnt] = fork();
	if (command->hold_pid[com_cnt] == 0)
	{
		ft_signals(CHI_SEGNAL);
		dup2(command->pipeline[(com_cnt + 1) % 2][0], 0);
		dup2(command->pipeline[com_cnt % 2][1], 1);
		close_all(command->pipeline, com_cnt);
		env = env_to_array(*command->env);
		execve(path, tokens, env);
		exit(1);
	}
}
