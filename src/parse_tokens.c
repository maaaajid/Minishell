/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 08:51:32 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 22:27:02 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	check_iflastop_pip(int *com)
{
	int	i;

	i = 0;
	while (com[i])
		i++;
	if (com[i - 1] && com[i - 1] == PIPELINE)
	{
		ft_printf(2, "minishell: parse error `|'\n");
		return (true);
	}
	return (false);
}

static bool	check_for_maxheredoc(int *com)
{
	int	hd;
	int	i;

	i = 0;
	hd = 0;
	while (com[i])
	{
		if (com[i] == HER_SIGNAL)
			hd += 1;
		i++;
	}
	if (hd > 15)
	{
		g_exit_status = 2;
		ft_printf(2, "minishell: maximum hd exceeded\n");
		return (false);
	}
	return (true);
}

static bool	check_for_filesop(int *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == RED_INPUT_SIGNAL && cmd[i + 1] != RED_INPUT_FILE)
			return (false);
		if (cmd[i] == RED_OUTPUT_SIGNAL && cmd[i + 1] != RED_OUTPUT_FILE)
			return (false);
		if (cmd[i] == APPEND_O_SIGNAL && cmd[i + 1] != APPEND_O_FILE)
			return (false);
		if (cmd[i] == HER_SIGNAL && cmd[i + 1] != HER_LIMITER)
			return (false);
		i++;
	}
	return (true);
}

bool	is_op_doubled(int *com)
{
	int		i;

	i = 0;
	while (com[i])
	{
		if (com[i] == PIPELINE && com[i + 1] == PIPELINE)
		{
			ft_printf(2, "minishell: syntax error unexpected token `|'\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_command(int *com)
{
	if (!is_op_doubled(com))
	{
		g_exit_status = 2;
		return (false);
	}
	if (check_iflastop_pip(com))
	{
		g_exit_status = 2;
		return (false);
	}
	if (!check_for_filesop(com))
	{
		g_exit_status = 2;
		ft_printf(2, "minishell: syntax error: near unexpected token\n");
		return (false);
	}
	if (!check_for_maxheredoc(com))
		return (false);
	return (true);
}
