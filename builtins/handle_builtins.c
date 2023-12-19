/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 07:20:11 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/26 01:12:32 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	launch_env_builtin(char **cmd_array, int *token_array,
			t_command *command)
{
	char	**arg_array;
	int		i;

	i = 0;
	if (!cmd_array || !token_array)
		return ;
	while (cmd_array[i] && token_array[i] != COM_NAME)
		i++;
	if (!cmd_array[i])
		return ;
	arg_array = command_args(cmd_array, token_array, NULL, NULL);
	if (!ft_strcmp(cmd_array[i], "cd"))
		ft_cd(arg_array, *command->env);
	else if (!ft_strcmp(cmd_array[i], "export"))
		ft_export(arg_array, command->env);
	else if (!ft_strcmp(cmd_array[i], "unset"))
		ft_unset(arg_array, command->env);
	else if (!ft_strcmp(cmd_array[i], "exit"))
	{
		close(command->pipeline[0][1]);
		close(command->pipeline[1][0]);
		ft_exit(cmd_array);
	}
	ft_free((void **)arg_array);
}

static void	check_builtins(char **cmd_array, int *token_array,
			t_command *command, int cmd_nb)
{
	char	**arg_array;

	arg_array = command_args(cmd_array, token_array, NULL, NULL);
	if (!ft_strcmp(arg_array[0], "echo"))
		ft_echo(arg_array, token_array);
	else if (!ft_strcmp(arg_array[0], "env"))
		ft_env(arg_array, *command->env);
	else if (!ft_strcmp(arg_array[0], "pwd"))
		ft_pwd(*command->env);
	else if (!ft_strcmp(arg_array[0], "exit"))
		close_fd(command->pipeline[cmd_nb % 2][0]);
	ft_free((void **)arg_array);
}

void	close_fd(int fd)
{
	if (fd != -1)
		close(fd);
}

void	launch_builtin(char **cmd_array, int *token_array, t_command *command,
			int cmd_num)
{
	if (command->pipeline[(cmd_num + 1) % 2][0] == -1
		|| command->pipeline[cmd_num % 2][1] == -1)
		return ;
	command->hold_pid[cmd_num] = fork();
	if (command->hold_pid[cmd_num] == 0)
	{
		dup2(command->pipeline[(cmd_num + 1) % 2][0], 0);
		dup2(command->pipeline[cmd_num % 2][1], 1);
		close_fd(command->pipeline[(cmd_num + 1) % 2][0]);
		close_fd(command->pipeline[cmd_num % 2][1]);
		check_builtins(cmd_array, token_array, command, cmd_num);
		close_fd(command->pipeline[cmd_num % 2][0]);
		close_hd(command->heredoc);
		ft_list_clear(command->env);
		ft_free_command(command, NULL, NULL);
		exit(g_exit_status);
	}
}

int	check_for_builtin(char **cmd_array, int *token_array)
{
	int	i;

	i = 0;
	while (cmd_array && cmd_array[i] && token_array && token_array[i]
		!= COM_NAME && token_array[i] != COM_ARGUMENT)
		i++;
	if (!cmd_array[i])
		return (0);
	if (!ft_strcmp(cmd_array[i], "echo")
		|| !ft_strcmp(cmd_array[i], "env")
		|| !ft_strcmp(cmd_array[i], "pwd")
		|| !ft_strcmp(cmd_array[i], "cd")
		|| !ft_strcmp(cmd_array[i], "export")
		|| !ft_strcmp(cmd_array[i], "unset")
		|| !ft_strcmp(cmd_array[i], "exit"))
		return (1);
	return (0);
}
