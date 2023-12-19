/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 07:25:43 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 08:33:46 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	initialize_heredocs(int hd[15][2])
{
	int	i;

	i = 0;
	while (i < 15)
	{
		hd[i][0] = -1;
		hd[i][1] = -1;
		i++;
	}
}

static void	read_input(char *del, int st)
{
	char	*buffer;

	ft_signals(HER_SEGNAL);
	buffer = readline("> ");
	while (buffer && ft_strcmp(buffer, del))
	{
		ft_printf(st, "%s\n", buffer);
		free(buffer);
		buffer = readline("> ");
	}
	if (!status())
		ft_printf(1, "\n");
	else if (!buffer)
		ft_printf(2, HD_ERROR, del);
	free(buffer);
	ft_signals(DEF_SEGNAL);
	return ;
}

static int	read_heredoc(char *del)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	read_input(del, fd[1]);
	close(fd[1]);
	return (fd[0]);
}

static void	open_hd(int hd[15][2], char ***commands, int **tokens)
{
	int	com_cnt;
	int	i;
	int	j;

	com_cnt = 0;
	j = 0;
	initialize_heredocs(hd);
	while (commands[com_cnt] && status())
	{
		i = 0;
		while (commands[com_cnt][i] && status())
		{
			if (tokens[com_cnt][i] == HER_LIMITER)
			{
				if (hd[j][0] == com_cnt)
					close_fd(hd[j][1]);
				hd[j][1] = read_heredoc(commands[com_cnt][i]);
				hd[j][0] = com_cnt;
			}
			i++;
		}
		if (hd[j][0] == com_cnt)
			j++;
		com_cnt++;
	}
}

int	heredoc(int hd[15][2], char ***commands, int **tokens)
{
	int	buckstdin;

	buckstdin = dup(0);
	open_hd(hd, commands, tokens);
	if (!status())
	{
		dup2(buckstdin, 0);
		close(buckstdin);
		close_hd(hd);
		return (1);
	}
	close(buckstdin);
	return (0);
}
