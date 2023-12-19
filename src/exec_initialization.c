/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_initialization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 02:16:05 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/26 05:03:21 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	wait_all_chprocess(int *holdpid, int cmds_cnt)
{
	int	state;
	int	id;

	id = 0;
	while (id < cmds_cnt)
	{
		if (holdpid[id] != -1)
		{
			waitpid(holdpid[id], &state, 0);
			if (WIFEXITED(state))
				g_exit_status = WEXITSTATUS(state);
			else if (WIFSIGNALED(state))
			{
				if (WTERMSIG(state) == 2)
					g_exit_status = 130;
				else if (WTERMSIG(state) == 3)
					g_exit_status = 131;
				else if (WTERMSIG(state) == 11)
					g_exit_status = 139;
			}
		}
		id++;
	}
}

static void	iterate_over_commands(t_command *c, int i, char *path, char **toks)
{
	while (c->command_segments[i] && handle_redirections(c, i))
	{
		path = NULL;
		toks = NULL;
		if (check_for_builtin(c->command_segments[i], c->token_types[i]))
			launch_builtin(c->command_segments[i], c->token_types[i], c, i);
		else
		{
			g_exit_status = 0;
			path = get_thepath(c->command_segments[i],
					c->token_types[i], *c->env);
			if (path == NULL && g_exit_status && ++i)
				continue ;
			toks = command_args(c->command_segments[i],
					c->token_types[i], *c->env, path);
			execute_commands(toks, i, path, c);
			if (i < c->com_count - 1)
				(free(path), ft_free((void **)toks));
		}
		close_fd(c->pipeline[(++i % 2)][0]);
		close_fd(c->pipeline[(i + 1) % 2][1]);
	}
	wait_all_chprocess(c->hold_pid, c->com_count);
	last_command_sts(c, i - 1, path, toks);
}

static void	launch_command(t_command *cmd)
{
	cmd->pipeline[0][0] = -1;
	cmd->pipeline[0][1] = -1;
	cmd->pipeline[1][0] = -1;
	cmd->pipeline[1][1] = -1;
	if (check_env_buil(cmd->command_segments[0], cmd->token_types[0])
		&& cmd->com_count == 1)
	{
		handle_redirections(cmd, 0);
		launch_env_builtin(cmd->command_segments[0], cmd->token_types[0], cmd);
		close_fd(cmd->pipeline[0][1]);
		close_fd(cmd->pipeline[1][0]);
		return ;
	}
	else
		iterate_over_commands(cmd, 0, NULL, NULL);
	ft_signals(DEF_SEGNAL);
}

void	command_initial(char *op_com, t_env **env)
{
	int			i;
	t_command	*cmd;

	cmd = command_ini(op_com, *env);
	if (!cmd || !cmd->original_tokens)
		return ;
	cmd->env = env;
	cmd->com_count = com_cnt(cmd->original_commands, cmd->original_tokens);
	cmd->hold_pid = malloc(sizeof(int) * (cmd->com_count + 1));
	if (heredoc(cmd->heredoc, cmd->command_segments, cmd->token_types))
		g_exit_status = 1;
	else if (cmd->hold_pid)
	{
		i = 0;
		while (i < cmd->com_count)
			cmd->hold_pid[i++] = -1;
		cmd->hold_pid[i] = 0;
		launch_command(cmd);
	}
	ft_free_command(cmd, NULL, NULL);
}
