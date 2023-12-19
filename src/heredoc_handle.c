/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun < lahamoun@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 01:36:42 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/19 16:24:59 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_prev_hd(int heredoc[15][2], int com_cnt)
{
	int	i;

	i = 0;
	while (i < 15)
	{
		if (heredoc[i][0] == com_cnt)
			close(heredoc[i][1]);
		i++;
	}
}

static int	get_index_lasthd(int *args)
{
	int	hered;
	int	i;

	i = 0;
	hered = -1;
	while (args[i])
	{
		if (args[i] == HER_LIMITER)
			hered = i;
		i++;
	}
	return (hered);
}

static int	heredoc_fd(int hd[16][2], int com_cnt)
{
	int	i;

	i = 0;
	while (i < 16 && hd[i][0] != -1)
	{
		if (hd[i][0] == com_cnt)
			return (hd[i][1]);
		i++;
	}
	return (-1);
}

void	close_hd(int hd[15][2])
{
	int	i;

	i = 0;
	while (i < 15)
	{
		if (hd[i][0] != -1)
			close_fd(hd[i][1]);
		i++;
	}
}

int	chek_herdoc_state(int fd, t_command *command, int com_cnt)
{
	int	i;

	i = get_index_lasthd(command->token_types[com_cnt]);
	if (i == -1)
		return (fd);
	while (command->command_segments[com_cnt][i])
	{
		if (command->token_types[com_cnt][i] == RED_INPUT_FILE)
		{
			close_fd(heredoc_fd(command->heredoc, com_cnt));
			return (fd);
		}
		i++;
	}
	i = heredoc_fd(command->heredoc, com_cnt);
	if (i == -1)
		return (fd);
	else
	{
		close_fd(fd);
		return (i);
	}
}
