/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:36:08 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 08:22:16 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*new_token(char *value, bool is_quoted)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		printf("minishell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	token->value = value;
	token->is_quoted = is_quoted;
	token->next = NULL;
	return (token);
}

void	change_value_state(int *st, int c)
{
	if (c == '\'')
	{
		if (*st == 1)
			*st = 0;
		else if (*st == 0)
			*st = 1;
	}
	if (c == '\"')
	{
		if (*st == 2)
			*st = 0;
		else if (*st == 0)
			*st = 2;
	}
}

bool	check_str(const char *line, const char *str)
{
	int		i;
	int		j;
	int		st;

	i = 0;
	st = 0;
	while (line[i])
	{
		change_value_state(&st, line[i]);
		j = 0;
		while (st == 0 && str[j])
		{
			if (line[i] == str[j])
			{
				ft_printf(2, "minishell: syntax error: `%c' in input\n", str[j]);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	is_it_pipeline(const char *str)
{
	if (str[0] == '|')
	{
		ft_printf(2, "minishell: syntax error near unexpected token `|'\n");
		return (false);
	}
	return (true);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}
