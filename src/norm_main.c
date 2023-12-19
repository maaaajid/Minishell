/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouaa <aelbouaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:50:26 by aelbouaa          #+#    #+#             */
/*   Updated: 2023/06/25 08:47:04 by aelbouaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	norm_main(char *line, t_norm *nor, t_token **head, t_token **tail)
{
	t_token	*new;

	nor->quote = '\0';
	new = new_token(ft_strndup(&line[nor->start], nor->i - nor->start), true);
	if (!*head)
		*head = new;
	else
		(*tail)->next = new;
	*tail = new;
	nor->start = -1;
}

void	false_case(char *line, t_norm *nor, t_token **head, t_token **tail)
{
	t_token	*new;

	new = new_token(ft_strndup(&line[nor->start], nor->i - nor->start), false);
	if (!*head)
		*head = new;
	else
		(*tail)->next = new;
	*tail = new;
}

void	last_one(char *line, t_norm *nor, t_token **head, t_token **tail)
{
	t_token	*new;

	new = new_token(ft_strndup(&line[nor->start], nor->i - nor->start), false);
	if (!*head)
		*head = new;
	else
		(*tail)->next = new;
}

void	norm_helper(char *line, t_norm *norm, t_token **head, t_token **tail)
{
	if (norm->quote)
	{
		if (line[norm->i] == norm->quote)
			norm_main(line, norm, head, tail);
	}
	else if (line[norm->i] == '\'' || line[norm->i] == '\"')
	{
		norm->quote = line[norm->i];
		if (norm->start >= 0)
			false_case(line, norm, head, tail);
		norm->start = norm->i + 1;
	}
	else if (is_whitespace(line[norm->i]))
	{
		if (norm->start >= 0)
		{
			false_case(line, norm, head, tail);
			norm->start = -1;
		}
	}
	else if (norm->start < 0)
		norm->start = norm->i;
}
