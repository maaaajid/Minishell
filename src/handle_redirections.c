/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:39:14 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/26 05:02:27 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	out_open(char *f_name, int st)
{
	int	fd;
	int	mode;

	mode = O_TRUNC;
	if (st == APPEND_O_FILE)
		mode = O_APPEND;
	fd = open(f_name, O_WRONLY | O_CREAT | mode, 0644);
	if (fd == -1)
	{
		ft_printf(2, "minishell: ");
		perror(f_name);
	}
	return (fd);
}

static int	in_open(char *f_name, int st)
{
	int	fd;

	if (st == HER_LIMITER)
		return (0);
	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		ft_printf(2, "minishell: ");
		perror(f_name);
	}
	return (fd);
}

static void	search_file(t_command *cm, int c, int pipeline[2][2], int i)
{
	int	fd[2];

	fd[0] = pipeline[(c + 1) % 2][0];
	fd[1] = pipeline[c % 2][1];
	while (cm->command_segments[c][++i] && fd[0] != -1 && fd[1] != -1)
	{
		if (cm->token_types[c][i] == RED_OUTPUT_FILE
				|| cm->token_types[c][i] == APPEND_O_FILE)
		{
			close_fd(fd[1]);
			fd[1] = out_open(cm->command_segments[c][i], cm->token_types[c][i]);
		}
		else if (cm->token_types[c][i] == RED_INPUT_FILE)
		{
			close_fd(fd[0]);
			fd[0] = in_open(cm->command_segments[c][i], cm->token_types[c][i]);
		}
	}
	if (fd[0] != -1 && fd[1] != -1)
		fd[0] = chek_herdoc_state(fd[0], cm, c);
	else
		close_prev_hd(cm->heredoc, c);
	pipeline[(c + 1) % 2][0] = fd[0];
	pipeline[c % 2][1] = fd[1];
}

int	handle_redirections(t_command *cmd, int com_cnt)
{
	if (cmd->com_count == 1 && com_cnt == 0)
	{
		cmd->pipeline[1][0] = dup(0);
		cmd->pipeline[0][1] = dup(1);
		search_file(cmd, com_cnt, cmd->pipeline, -1);
		return (1);
	}
	if (com_cnt == 0)
	{
		pipe(cmd->pipeline[0]);
		cmd->pipeline[1][0] = dup(0);
		search_file(cmd, com_cnt, cmd->pipeline, -1);
		return (1);
	}
	if (com_cnt == cmd->com_count - 1)
	{
		cmd->pipeline[com_cnt % 2][1] = dup(1);
		search_file(cmd, com_cnt, cmd->pipeline, -1);
		return (1);
	}
	pipe(cmd->pipeline[com_cnt % 2]);
	search_file(cmd, com_cnt, cmd->pipeline, -1);
	return (1);
}
