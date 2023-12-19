/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgnals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 00:25:12 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/26 02:13:06 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	heredoc_s(int s)
{
	(void)s;
	close(0);
}

void	general_s(int s)
{
	(void)s;
	g_exit_status = 1;
	ft_printf(1, "\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sp(int s)
{
	if (s == SIGINT)
		ft_printf(1, "\n");
	else if (s == SIGQUIT)
		ft_printf(2, "(Quit)\n");
}

void	ft_signals(int check)
{
	if (check == DEF_SEGNAL)
	{
		signal(SIGINT, general_s);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (check == HER_SEGNAL)
	{
		signal(SIGINT, &heredoc_s);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (check == CHI_SEGNAL)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	else if (check == PAR_SEGNAL)
	{
		signal(SIGINT, &sp);
		signal(SIGQUIT, &sp);
	}
}
