/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 01:42:52 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 22:29:18 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	norm_check(char **command, int i)
{
	if (i == 0 && command[i][0] == '|')
	{
		ft_printf(2, "minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

static void	ensure_op_token(char *command, int *comtype)
{
	if (command[0] == '|')
		*comtype = PIPELINE;
	else if (ft_strlen(command) > 1 && command[0] == '<')
		*comtype = HER_SIGNAL;
	else if (ft_strlen(command) > 1 && command[0] == '>')
		*comtype = APPEND_O_SIGNAL;
	else if (command[0] == '<')
		*comtype = RED_INPUT_SIGNAL;
	else if (command[0] == '>')
		*comtype = RED_OUTPUT_SIGNAL;
}

static bool	is_operator(char c, char *op)
{
	int	i;

	i = 0;
	while (op[i])
	{
		if (op[i] == c)
			return (true);
		i++;
	}
	return (false);
}

static void	ensure_type_of_tok(char **command, int **comtype, int i,
	bool *is_pipe)
{
	if (!norm_check(command, i))
		return ;
	if (is_operator(command[i][0], "<>|"))
	{
		ensure_op_token(command[i], &(*comtype)[i]);
		if ((*comtype)[i] == PIPELINE)
			*is_pipe = false;
	}
	else if (i > 0 && (*comtype)[i - 1] == HER_SIGNAL)
		(*comtype)[i] = HER_LIMITER;
	else if (i > 0 && (*comtype)[i - 1] == RED_INPUT_SIGNAL)
		(*comtype)[i] = RED_INPUT_FILE;
	else if (i > 0 && (*comtype)[i - 1] == RED_OUTPUT_SIGNAL)
		(*comtype)[i] = RED_OUTPUT_FILE;
	else if (i > 0 && (*comtype)[i - 1] == APPEND_O_SIGNAL)
		(*comtype)[i] = APPEND_O_FILE;
	else if ((i > 0 && (*comtype)[i - 1] == COM_NAME)
			|| (i > 0 && (*comtype)[i - 1] == COM_ARGUMENT) || *is_pipe == true)
		(*comtype)[i] = COM_ARGUMENT;
	else
	{
		(*comtype)[i] = COM_NAME;
		*is_pipe = true;
	}
}

int	*tokenization(char **cmd)
{
	int		i;
	int		*comtype;
	bool	is_pipe;

	comtype = ft_calloc(sizeof(int), ft_arrlen(cmd) + 1);
	if (!comtype)
		return (NULL);
	i = 0;
	is_pipe = false;
	while (cmd[i])
	{
		ensure_type_of_tok(cmd, &comtype, i, &is_pipe);
		i++;
	}
	if (check_command(comtype))
		return (comtype);
	g_exit_status = 2;
	free(comtype);
	return (NULL);
}
