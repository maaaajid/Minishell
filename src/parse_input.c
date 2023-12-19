/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:36:23 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 22:26:29 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	is_quote_unclose(const char *line)
{
	int		i;
	int		state;

	i = 0;
	state = 0;
	while (line[i])
	{
		change_value_state(&state, line[i]);
		i++;
	}
	if (state == 1)
	{
		ft_printf(2, "minishell: ' not closed\n");
		return (false);
	}
	else if (state == 2)
	{
		ft_printf(2, "minishell: \" not closed\n");
		return (false);
	}
	return (true);
}

static bool	check_for_op(const char *line, const char c, const int n)
{
	int		i;
	int		op_nb;
	int		st;

	i = -1;
	st = 0;
	while (line[++i])
	{
		change_value_state(&st, line[i]);
		op_nb = 0;
		while (line[i] && st == 0 && line[i] == c)
		{
			op_nb++;
			i++;
			change_value_state(&st, line[i]);
		}
		if (st == 0 && op_nb > n)
		{
			ft_printf(2, OP_ERROR, c, c);
			return (false);
		}
		if (!line[i])
			break ;
	}
	return (true);
}

static bool	is_unknown_op(const char *line)
{
	int		i;
	int		st;

	i = 0;
	st = 0;
	while (line[i])
	{
		change_value_state(&st, line[i]);
		if ((st == 0 && line[i] == '>') || (st == 0 && line[i] == '<'))
		{
			if ((line[i] == '>' && line[i + 1] == '<')
				|| (line[i] == '<' && line[i + 1] == '>'))
			{
				ft_printf(2, "minishell: syntax error: unexpected operator\n");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

bool	isempty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
		i++;
	if (line[i] == 0)
		return (true);
	return (false);
}

t_token	*breakdown_line(char *line)
{
	t_token	*tokens;

	tokens = NULL;
	if (!line || isempty_line(line))
		return (NULL);
	if (!is_quote_unclose(line) || !check_for_op(line, '<', 2)
		|| !check_for_op(line, '>', 2)
		|| !check_for_op(line, '|', 1) || !check_str(line, ";\\&")
		|| !is_unknown_op(line) || !is_it_pipeline(line))
	{
		g_exit_status = 2;
		return (NULL);
	}
	tokens = parse_quotes(line);
	return (tokens);
}
