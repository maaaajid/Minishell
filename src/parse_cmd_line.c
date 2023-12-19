/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:07:18 by lahamoun          #+#    #+#             */
/*   Updated: 2023/06/25 07:00:15 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	len_ofnext_token(char *com)
{
	int	i;
	int	q_status;

	q_status = 0;
	i = 0;
	while (com && com[i])
	{
		if (com[i] == '\'' || com[i] == '\"')
			change_value_state(&q_status, com[i]);
		i++;
		if (check_space(com[i]) && !q_status)
			break ;
	}
	return (i);
}

static int	token_count(char *com)
{
	int	i;
	int	n;
	int	q_status;

	q_status = 0;
	n = 0;
	i = 0;
	while (com && com[i])
	{
		if (com[i] == '\'' || com[i] == '\"')
			change_value_state(&q_status, com[i]);
		i++;
		if (check_space(com[i]) && !q_status)
		{
			while (com[i] && check_space(com[i]))
				i++;
			if (com[i])
				n++;
		}
	}
	return (n + (q_status == 0));
}

char	**splt_commands(char *com)
{
	int		i;
	char	**tokens;
	int		tokens_cnt;
	int		len;

	while (com && *com && check_space(*com))
		com++;
	tokens_cnt = token_count(com);
	tokens = malloc((tokens_cnt + 1) * sizeof(char *));
	tokens[tokens_cnt] = NULL;
	i = 0;
	while (i < tokens_cnt)
	{
		len = len_ofnext_token(com);
		tokens[i] = ft_substr(com, 0, len);
		com += len + (com[len] != '\0');
		while (*com && check_space(*com))
			com++;
		i++;
	}
	return (tokens);
}
