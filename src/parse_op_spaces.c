/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_op_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:06:57 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 22:26:40 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*insert_space_before_operator(char *tok, int i)
{
	char	*temp;
	char	*ptr;
	char	*t_emp;

	temp = ft_substr(tok, 0, i);
	t_emp = ft_strjoin(temp, " ");
	free (temp);
	temp = ft_substr(tok, i, ft_strlen(tok) - i);
	ptr = ft_strjoin(t_emp, temp);
	free (temp);
	free (t_emp);
	free (tok);
	return (ptr);
}

char	*insert_space_after_operator(char *tok, int i)
{
	char	*ptr;
	char	*temp;
	char	*t_emp;

	temp = ft_substr(tok, 0, i + 1);
	t_emp = ft_strjoin(temp, " ");
	free (temp);
	temp = ft_substr(tok, i + 1, ft_strlen(tok) - (i + 1));
	ptr = ft_strjoin(t_emp, temp);
	free (temp);
	free (t_emp);
	free (tok);
	return (ptr);
}

char	*ensure_space_after_operator(char *command, int i, int *len)
{
	if ((command[i + 1] && !check_for_space(command[i + 1])
			&& !check_for_redirection(command[i + 1])) || *len == 2)
	{
		command = insert_space_after_operator(command, i);
		*len = 0;
	}
	else
		*len = 0;
	return (command);
}

char	*parse_after_operators(char *cmd)
{
	char	*command;
	int		i;
	int		st;
	int		len;

	i = -1;
	len = 0;
	st = 0;
	command = cmd;
	while (command[++i])
	{	
		change_value_state(&st, command[i]);
		if (st == 0 && (check_for_redirection(command[i])
				|| check_for_pipe(command[i])))
		{
			if (check_for_redirection(command[i]))
				len += 1;
			command = ensure_space_after_operator(command, i, &len);
		}
	}
	return (command);
}

char	*input_parse_op(char *cmd)
{
	int		i;
	int		st;
	char	*command;

	i = 0;
	st = 0;
	command = ft_strdup(cmd);
	if (!ft_strcmp(cmd, "|"))
		g_exit_status = 0;
	while (command[i])
	{
		change_value_state(&st, command[i]);
		if (st == 0 && (check_for_redirection(command[i])
				|| check_for_pipe(command[i])))
		{
			if (i > 1 && ft_strlen(command) > 1
				&& !check_for_space(command[i - 1])
				&& !check_for_redirection(command[i - 1]))
				command = insert_space_before_operator(command, i);
		}
		i++;
	}
	command = parse_after_operators(command);
	return (command);
}
